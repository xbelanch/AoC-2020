#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXBUFFER 2048

// https://stackoverflow.com/questions/35178520/how-to-read-parse-input-in-c-the-faq
void parseInput(char* filename) {

    FILE* fp = fopen(filename, "rb");

    if (!fp)
        fprintf(stderr, "Cannot open %s: %s\n", filename, strerror(errno));

    char* buffer = malloc(sizeof(char) * MAXBUFFER);
    int line = 0;
    int newline = 0;

    printf("Passport %d: \n", newline + 1);
    while ( fgets(buffer, MAXBUFFER, fp) != NULL) {

        if (buffer[0] == '\r' && buffer[1] == '\n' ) {
            newline++;
            printf("Passport %d: \n", newline + 1);
            continue;
        } else {
            printf("%d>%s", line, buffer);
            line++;
        }
    }

    fclose(fp);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        parseInput(argv[i]);
    }
    return 0;
}
