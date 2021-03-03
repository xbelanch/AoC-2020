CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -g
LIBS=
INPUT=sample-01.txt

.PHONY: test

test: main $(INPUT)
	./main.exe $(INPUT)

main: main.c
	    $(CC) $(CFLAGS) -o main main.c $(LIBS)
