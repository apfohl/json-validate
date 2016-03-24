BIN = json-validate

CFLAGS = -g -Wall -std=gnu11
LDLIBS = -ljzon

.PHONY: all release clean

all: $(BIN)

release: CFLAGS = -std=gnu11 -Os -march=native -flto -Wall -Wextra -Wpedantic -Wstrict-overflow -fno-strict-aliasing
release: $(BIN)

clean:
	rm -r $(BIN)
	rm -rf *.dSYM
