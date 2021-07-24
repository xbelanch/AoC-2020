CFLAGS=-std=c11 -pedantic -DPART_TWO -ggdb
LIBS=./hashmap.c/hashmap.c
INPUT= input.txt

.PHONY: test

test: main $(INPUT)
	./main $(INPUT)

main: main.c
	$(CC) $(CFLAGS) -o main main.c $(LIBS)
