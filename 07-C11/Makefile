CC=gcc
CXXFLAGS=-Wall -Wextra -std=c11 -pedantic -g
INPUT=sample-01.txt

.PHONY: test

test: main
	./main.exe $(INPUT)

viz: main
	./main.exe $(INPUT) > rules.dot

main: main.c
	$(CC) $(CXXFLAGS) -o main main.c
