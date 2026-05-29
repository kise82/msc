CC := clang
CFLAGS := -pipe -fPIE -O2 -std=c11 -Iinclude/

SRC := $(wildcard src/*.c)
OBJ := $(patsubst %.c,%.o,$(patsubst src/%,build/%,${SRC}))

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
