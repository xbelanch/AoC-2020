CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=
INPUT=

.PHONY: test

test: main.c $(INPUT)
	./main $(INPUT)

main.c:
	$(CC) $(CFLAGS) main.c -o main $(LIBS)
