CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb -Wsign-compare
LIBS=
INPUT=sample-01.txt sample-02.txt

.PHONY: all

all: main $(INPUT)
	./main $(INPUT)
main: main.c
	$(CC) $(CFLAGS) -o main main.c $(LIBS)
test: crt.c
	$(CC) $(CFLAGS) -o crt crt.c
	./crt
