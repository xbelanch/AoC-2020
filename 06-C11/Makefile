CC=gcc
CXXFLAGS=-Wall -Wextra -std=c11 -pedantic -g
INPUT=sample-02.txt input.txt

.PHONY: test

test: main
	./main $(INPUT)

main: main.c
	$(CC) $(CXXFLAGS) -o main main.c
