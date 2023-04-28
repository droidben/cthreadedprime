CC=gcc
CFLAGS=-std=c99 -pedantic -pedantic-errors -Werror -Wall -Wextra -g -pthread

all: threadedprime

threadedprime: threadedprime.c

clean:
	rm -f threadedprime
