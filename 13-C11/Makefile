CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb
LIBS=
INPUT=sample-01.txt

.PHONY: all

all: main $(INPUT)
	./main $(INPUT)
main: main.c
	$(CC) $(CFLAGS) -o main main.c $(LIBS)
