CC=gcc
CXXFLAGS=-Wall -Wextra -std=c99 -pedantic -Wunused-but-set-variable -Wunused-variable -Wunused-parameter -Wsizeof-pointer-div
INPUTS=input.txt

.PHONY: test
test: main
	./main $(INPUTS)

main: main.c
	$(CC) $(CXXFLAGS) -o main main.c
