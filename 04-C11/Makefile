CC=gcc
CXXFLAGS=-Wall -Wextra -std=c11 -pedantic -Wunused-but-set-variable -Wunused-variable -Wunused-parameter -Wsizeof-pointer-div
INPUT=test.txt input.txt

.PHONY: test

test: main
	./main $(INPUT)

main: main.c
	$(CC) $(CXXFLAGS) -o main main.c
