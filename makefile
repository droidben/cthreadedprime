CC=gcc
CFLAGS=-std=c99 -pedantic -pedantic-errors -Werror -Wall -Wextra

all: threadedprime

threadedprime: threadedprime.c

clean:
	rm -f threadedprime
