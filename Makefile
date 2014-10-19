# See LICENSE file for copyright and license details.

.POSIX:

include config.mk

SRC = munge_pg_93_to_82.c
OBJ = ${SRC:.c=.o}

all: munge_pg_93_to_82

.c.o:
	@echo CC $<
	@${CC} -g -c ${CFLAGS} $<

munge_pg_93_to_82: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${LDFLAGS} ${OBJ}

clean:
	@echo cleaning
	@rm -f munge_pg_93_to_82 ${OBJ}

.PHONY: all options clean munge_pg_93_to_82
