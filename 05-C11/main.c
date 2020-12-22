#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFFER 2048
#define MAXLINES 2048

// sample: FBFBBFFRLR
char* entries[2048];

void printEntries() {
    for (int i = 0; entries[i] != NULL; i++) {
        printf("%d>%s\n", i, entries[i]);
    }
}

void parseInput(char* filename) {

    FILE *fp = fopen(filename, "r");
    char *fileBuffer = malloc(sizeof(char) * MAXBUFFER);

    int line = 0;
    while (fgets(fileBuffer, MAXBUFFER, fp) != NULL) {
        entries[line] = malloc(sizeof(char) * 10);
        entries[line][0] = '\0';
        strcpy(entries[line], fileBuffer);
    }

    printEntries();

    free(fileBuffer);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        parseInput(argv[i]);
    }
    return 0;
}
