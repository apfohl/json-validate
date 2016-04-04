#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <jzon.h>

int main(int argc, const char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "No argument given!\n");
        return EXIT_FAILURE;
    }

    struct stat buf;
    if (stat(argv[1], &buf) != 0) {
        perror("stat");
        return EXIT_FAILURE;
    }

    FILE *fd = fopen(argv[1], "r");
    if (!fd) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    char *data = calloc(buf.st_size + 1, sizeof(char));

    off_t r = fread(data, sizeof(char), buf.st_size, fd);
    if (r < buf.st_size) {
        fprintf(stderr, "Something went wrong while reading the file!\n");
        free(data);
        fclose(fd);
        return EXIT_FAILURE;
    }

    fclose(fd);

    data[buf.st_size] = '\0';

    clock_t start = clock();
    struct jzon *jzon = jzon_parse(data);
    clock_t stop = clock();
    fprintf(stderr, "jzon_parse took %f seconds.\n", (double)(stop - start) / CLOCKS_PER_SEC);
    if (!jzon) {
        fprintf(stderr, "Not valid JSON!\n");
        free(data);
        return EXIT_FAILURE;
    }

    free(data);

    fprintf(stdout, "Valid JSON!\n");

    jzon_free(jzon);

    return EXIT_SUCCESS;
}
