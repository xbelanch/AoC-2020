CC=gcc
CXXFLAGS=-Wall -Wextra -std=c11 -pedantic -Wunused-but-set-variable -Wunused-variable -Wunused-parameter -Wsizeof-pointer-div -Wunused-variable
INPUT=input.txt

.PHONY: test

test: main
	./main $(INPUT)

main: main.c
	$(CC) $(CXXFLAGS) -o main main.c
