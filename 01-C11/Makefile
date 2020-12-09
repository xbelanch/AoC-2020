CC=gcc
CXXFLAGS=-Wall -Wextra -std=c99 -pedantic
INPUTS=sample.txt input.txt

.PHONY: test
test: main
	./main

main: main.c
	$(CC) $(CXXFLAGS) -o main main.c
