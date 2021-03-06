CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=`pkg-config --libs --cflags sdl2`
INPUT=sample-01.txt input.txt

.PHONY: test

test: main $(INPUT)
	./main.exe $(INPUT)

main: main.c
	    $(CC) $(CFLAGS) -o main main.c
