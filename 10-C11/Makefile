CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -g
LIBS=
INPUT=sample-01.txt sample-02.txt tsoding.txt input.txt

.PHONY: all

all: main
	./main.exe $(INPUT)

main: main.c
	$(CC) $(CFLAGS) -o main main.c $(LIBS)
