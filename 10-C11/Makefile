CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -g
LIBS=
INPUT=sample-01.txt sample-02.txt tsoding.txt input.txt

.PHONY: all

all: main
	./main.exe $(INPUT)

fib: fib.c
	$(CC) $(CFLAGS) -o fib fib.c $(LIBS)
	./fib.exe 50

main: main.c fib.c
	$(CC) $(CFLAGS) -o main main.c $(LIBS)
