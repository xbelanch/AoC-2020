CC=gcc
CXXFLAGS=-Wall -Wextra -std=c11 -pedantic -g
INPUT=sample-01.txt input.txt tsoding.txt

.PHONY: all

all: main
	./main.exe $(INPUT)

test: sandbox
	./sandbox.exe $(INPUT)

viz: main
	./main.exe $(INPUT) > rules.dot

main: main.c
	$(CC) $(CXXFLAGS) -o main main.c

sandbox: sandbox.c
	$(CC) $(CXXFLAGS) -o sandbox sandbox.c
