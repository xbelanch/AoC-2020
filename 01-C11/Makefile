CC=gcc
CXXFLAGS=-Wall -Wextra -std=c99 -pedantic
INPUTS=sample.txt input.txt

.PHONY: test
test: main
	./main input.txt

main: main.c
	$(CC) $(CXXFLAGS) -o main main.c
