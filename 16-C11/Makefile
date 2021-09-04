CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=
INPUT=sample-input.txt

.PHONY: test

test: main $(INPUT)
	./main $(INPUT)

main: main3.c
	$(CC) $(CFLAGS) -o main main3.c $(LIBS)
