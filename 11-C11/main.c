#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 4096

typedef enum {
    isEmpty = 0,
    isOccupied = 1,
    isFloor = -1,
    isUnknown = 99
} State;


State checkSeatPosition(char **layout, int row, int column) {
    switch(layout[row][column]) {
    case 'L': return isEmpty;
    case '#': return isOccupied;
    case '.': break;
    }
    return isUnknown;
}

int checkRuleOne(char **layout, int size, int row, int column) {
    // * - * - *
    // |   |   |
    // * - L - *
    // |   |   |
    // * - * - *

    for (int i = row - 1; i <= row + 1; i++) {
        if (i >= 0 && i < size - 1) {
            for (int j = column - 1; j <= column + 1; j++) {
                if (j >= 0 && j < (int)strlen(layout[0])) {
                    if (checkSeatPosition(layout, i, j) == isOccupied)
                        return 1;
                }
            }
        }
    }
    return 0;
}

int checkRuleTwo(char **layout, int size, int row, int column) {

    int occupied = -1; // At the moment, a dummy way to don't count itself

    for (int i = row - 1; i <= row + 1; i++) {
        if (i >= 0 && i < size -1) {
            for (int j = column - 1; j <= column + 1; j++) {
                if (j >= 0 && j < (int)strlen(layout[0])) {
                    if (checkSeatPosition(layout, i, j) == isOccupied)
                        occupied += 1;

                    if (occupied >= 4)
                        return 1;
                }
            }
        }
    }
    return 0;
}

int runOneCycle(char **layout, int size) {
    char *buffer[N + 1];
    int change = 0;
    for (int i = 0; i < size - 1; i++) {
        buffer[i] = malloc(sizeof(char) * N + 1);
        strcpy(buffer[i], layout[i]);
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; buffer[i][j]; j++) {
            if (buffer[i][j] == 'L' && checkRuleOne(buffer, size, i, j) == 0) {
                layout[i][j] = '#';
                change += 1;
            }
            if (buffer[i][j] == '#' && checkRuleTwo(buffer, size, i, j) == 1) {
                layout[i][j] = 'L';
                change += 1;
            }
        }
    }

    return change;
}

int countOccupiedSeats(char **layout, int size) {
    int occupiedSeats = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; layout[i][j]; j++) {
            if (layout[i][j] == '#')
                occupiedSeats++;
        }
    }

    return occupiedSeats;
}


// Print the seat layout
void printSeatLayout(char **layout, int size) {
    printf("Rows: %d\n", size - 1);
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; layout[i][j]; j++) {
            printf("%c", layout[i][j]);
        }
        printf("\n");
    }
}

void solve_file(char *filename) {
    printf("Input file: %s\n", filename);

    char *arr[N + 1];
    int arr_size = 0;
    FILE *f = fopen(filename, "rb");
    while (!feof(f)) {
        char buffer[N + 1];
        arr[arr_size] = malloc(sizeof(char) * N);
        fscanf(f, "%[^\n]%*c", buffer);
        strcpy(arr[arr_size++], buffer);
    }

    fclose(f);

    int cycles = 0;
    int run = 1;
    while (run) {
        if (runOneCycle(arr, arr_size) == 0)
            run = 0;
        cycles++;
    }

    printf("Cycles: %d\n", cycles);
    printf("How many seats end up occupied? %d\n", countOccupiedSeats(arr, arr_size));

}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
