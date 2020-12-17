#include <stdio.h>
#include <stdlib.h>

#define MAXLINEBUFFER 2048
#define log(string) printf("> %s", string)

void parseInput(char* filename) {
    puts(filename);

    FILE* file = fopen(filename, "r");
    char* line = malloc(sizeof(char) * MAXLINEBUFFER);

    while ( fgets(line, MAXLINEBUFFER, file) != NULL) {
        log(line);
    }
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        parseInput(argv[i]);
    }
    return 0;
}
