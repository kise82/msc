CC := clang
LINTS := -Wall -Wextra -Wpedantic -Wno-unused-parameter
CFLAGS := -g -pipe -fPIE -O2 -std=c11 -Iinclude/ ${LINTS}

SRC := $(shell find src/ -type f -name '*.c')
OBJ := $(patsubst %.c,%.o,$(patsubst src/%,build/%,${SRC}))

TEST := test/lexer-test

all: msc

msc: ${OBJ}
	${CC} -o $@ $^

build/%.o: src/%.c
	@mkdir -p ${@D}
	${CC} -c ${CFLAGS} -o $@ $^

.PHONY: clean
clean:
	rm -f msc
	rm -f ${OBJ}

.PHONY: test
test: ${TEST}
	test/lexer-test

test/lexer-test: test/lexer.c build/lexer.o
	${CC} -g ${CFLAGS} -o $@ $^

.PHONY: clean-test
clean-test:
	rm -f ${TEST}
