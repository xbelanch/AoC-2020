CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -g
LIBS=
INPUTS=sample-01.txt input.txt

.PHONY: test
test: main $(INPUTS)
	./main.exe $(INPUTS)

main: main.c
	$(CC) $(CFLAGS) -o main main.c $(LIBS)
