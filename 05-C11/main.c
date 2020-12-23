#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXBUFFER 2048
#define MAXLINES 2048
#define MAXROWS 128
#define MAXCOLUMNS 8


char* entries[MAXLINES];
char seats[MAXROWS][MAXCOLUMNS];

int getRow(char* entry) {
    // check first 7 characters
    // F means lower half
    // B means upper half
    // range of rows from 0 through 127
    int maxrange = MAXROWS - 1;
    int minrange = 0;
    int tmp = 0;
    for (int i = 0; i < 7; i++) {
        tmp = floor(maxrange - minrange);
        if (entry[i] == 'F') {
            maxrange = round(maxrange - (tmp / 2)) - 1;
        } else if (entry[i] == 'B') {
            minrange = round(minrange + (tmp / 2)) + 1;
        }
        /* printf(">%c rows %d through %d\n", entry[i], minrange, maxrange); */
    }

    if (minrange != maxrange)
        printf("Something went wrong!\n");

    return minrange;
}

int getColum(char* entry) {
    // check last 3 characters
    // R means upper half
    // L means lower half
    // range of 8 columns
    int maxrange = MAXCOLUMNS - 1;
    int minrange = 0;
    int tmp = 0;
    for (int i = 7; i < 10; i++) {
        tmp = floor(maxrange - minrange);
        if (entry[i] == 'L') {
            maxrange = round(maxrange - (tmp / 2)) - 1;
        } else if (entry[i] == 'R') {
            minrange = round(minrange + (tmp / 2)) + 1;
        }
        /* printf(">%c rows %d through %d\n", entry[i], minrange, maxrange); */
    }

    if (minrange != maxrange)
        printf("Something went wrong!\n");

    return minrange;
}

int parseEntry(char *entry) {
    int row = 0;
    int column = 0;

    // check first 7 characters
    // F means lower half
    // B means upper half
    // range of rows from 0 through 127
    int maxrange = MAXROWS - 1;
    int minrange = 0;
    int tmp = 0;
    for (int i = 0; i < 7; i++) {
        tmp = floor(maxrange - minrange);
        if (entry[i] == 'F') {
            maxrange = round(maxrange - (tmp / 2)) - 1;
        } else if (entry[i] == 'B') {
            minrange = round(minrange + (tmp / 2)) + 1;
        }
        /* printf(">%c rows %d through %d\n", entry[i], minrange, maxrange); */
    }

    if (minrange == maxrange) {
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
        /* printf(">%c rows %d through %d\n", entry[i], minrange, maxrange); */
    }

    if (minrange == maxrange) {
        column = minrange;
    } else {
        printf("Something went wrong!\n");
    }

    /* printf("The seat has ID %d\n", row * 8 + column); */
    return row * 8 + column;
}

void getSolutionPartOne() {
    int id = 0;
    int highest_seat_id = 0;
    for (int i = 0; entries[i] != NULL; i++) {
        /* printf("%d>%s\n", i, entries[i]); */
        id = parseEntry(entries[i]);
        if (id > highest_seat_id)
            highest_seat_id = id;
    }

    printf("What is the highest seat ID on a boarding pass: %d\n\n", highest_seat_id);
}

void partOne(char* filename) {

    FILE *fp = fopen(filename, "r");
    char *fileBuffer = malloc(sizeof(char) * MAXBUFFER);

    int line = 0;
    int len = 0;
    while (fgets(fileBuffer, MAXBUFFER, fp) != NULL) {
        len = strlen(fileBuffer);
        fileBuffer[len - 1] = '\0'; // remove carriage return
        entries[line] = malloc(sizeof(char));
        entries[line][0] = '\0';
        strcpy(entries[line], fileBuffer);
        line++;
    }

    getSolutionPartOne();

    free(fileBuffer);
    fclose(fp);
}

void initializeEmptySeats() {
    for (int row = 0; row < MAXROWS; row++) {
        for (int column = 0; column < MAXCOLUMNS; column++) {
            seats[row][column] = '-';
        }
    }
}

void displayFlySeats() {
    // display the seats by columns and rows
    // * -> occupied seat
    // - -> free seat
    printf("  \t01234567\n");
    for (int row = 0; row < MAXROWS; row++) {
        printf(">%d\t", row);
        for (int column = 0; column < MAXCOLUMNS ; column++) {
            printf("%c", seats[row][column]);
        }
        printf("\n");
    }
}


void getSolutionPartTwo() {

    int row = 0;
    int column = 0;

    initializeEmptySeats();

    for (int i = 0; entries[i] != NULL; i++) {
        row = getRow(entries[i]);
        column = getColum(entries[i]);
        seats[row][column] = '*';
    }

    displayFlySeats();

    // print all the free seats:
    printf("Free seats:\n");
    // Still dont understand the sentence:
    /* Your seat wasn't at the very front or back, though; the seats with IDs +1 and -1 from yours will be in your list. */
    for (int row = 12; row < 116 ; row++) {
        for (int column = 0; column < MAXCOLUMNS; column++) {
            if (seats[row][column] == '-') {
                printf("ID: %d, r: %d, c: %d\n", row * 8 + column, row, column);
            }
        }
    }
}


void partTwo(char* filename) {

    FILE *fp = fopen(filename, "r");
    char *fileBuffer = malloc(sizeof(char) * MAXBUFFER);

    int line = 0;
    int len = 0;
    while (fgets(fileBuffer, MAXBUFFER, fp) != NULL) {
        len = strlen(fileBuffer);
        fileBuffer[len - 1] = '\0'; // remove carriage return
        entries[line] = malloc(sizeof(char));
        entries[line][0] = '\0';
        strcpy(entries[line], fileBuffer);
        line++;
    }

    getSolutionPartTwo();

    free(fileBuffer);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        partOne(argv[i]);
        partTwo(argv[i]);
    }
    return 0;
}
