CC=gcc
CXXFLAGS=-Wall -Wextra -std=c11 -pedantic
INPUT=input.txt

.PHONY: test

test: main
	./main $(INPUT)

main: main.c
	$(CC) $(CXXFLAGS) -o main main.c
