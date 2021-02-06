CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -g
LIBS=
INPUT=tsoding.txt

.PHONY: all

all: main
	./main.exe $(INPUT)

main: main.c
	$(CC) $(CFLAGS) -o main main.c $(LIBS)
