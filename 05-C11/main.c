#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXBUFFER 2048
#define MAXLINES 2048

// sample: FBFBBFFRLR
char* entries[2048];

void parseEntry(char *entry) {
    int row = 0;
    int column = 0;

    // check first 7 characters
    // F means lower half
    // B means upper half
    // range of rows from 0 through 127
    int maxrange = 127;
    int minrange = 0;
    int tmp = 0;
    for (int i = 0; i < 7; i++) {
        tmp = floor(maxrange - minrange);
        if (entry[i] == 'F') {
            maxrange = round(maxrange - (tmp / 2)) - 1;
        } else if (entry[i] == 'B') {
            minrange = round(minrange + (tmp / 2)) + 1;
        }
        printf(">%c rows %d through %d\n", entry[i], minrange, maxrange);
    }

    if (minrange == maxrange) {
        printf("row %d\n", minrange);
        row = minrange;
    } else {
        printf("Something went wrong!\n");
    }

    // check last 3 characters
    // R means upper half
    // L means lower half
    // range of 8 columns
    maxrange = 7;
    minrange = 0;
    tmp = 0;
    for (int i = 7; i < 10; i++) {
        tmp = floor(maxrange - minrange);
        if (entry[i] == 'L') {
            maxrange = round(maxrange - (tmp / 2)) - 1;
        } else if (entry[i] == 'R') {
            minrange = round(minrange + (tmp / 2)) + 1;
        }
        printf(">%c rows %d through %d\n", entry[i], minrange, maxrange);
    }

    if (minrange == maxrange) {
        printf("column %d\n", minrange);
        column = minrange;
    } else {
        printf("Something went wrong!\n");
    }

    printf("The seat has ID %d\n", row * 8 + column);

}

void printEntries() {
    for (int i = 0; entries[i] != NULL; i++) {
        printf("%d>%s\n", i, entries[i]);
        parseEntry(entries[i]);
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
