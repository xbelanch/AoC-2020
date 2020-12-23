CC=gcc
CXXFLAGS=-Wall -Wextra -std=c11 -pedantic
INPUT=sample-01.txt

.PHONY: test

test: main
	./main $(INPUT)

main: main.c
	$(CC) $(CXXFLAGS) -o main main.c
