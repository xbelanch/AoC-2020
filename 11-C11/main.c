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

int* raycast(char **layout, int size, int row, int column) {

    // 0 -> occupied
    // 1 -> empty
    int* seats = malloc(sizeof(int) * 2);
    seats[0] = 0;
    seats[1] = 0;

    int width = (int) (strlen(layout[0]) - 1);

    for (int i = row - 1; i <= row + 1; i++) {
        if (i >= 0 && i <= size ) {
            for (int j = column - 1; j <= column + 1; j++) {
                if (j >= 0 && j < width) {
                    if (layout[i][j] == '.') {
                        // cast a ray until reaching limit of canvas seat
                        int dirX = j - column;
                        int dirY = i - row;
                        // Right
                        if (dirX == 1 && dirY == 0) {
                            for (int steps = 0; steps < (width - column - 1); steps++) {
                                if (layout[i][j + steps] != '#' && layout[i][j + steps] != 'L') {
                                    /* layout[i][j + steps] = '*'; */
                                }
                                if (layout[i][j + steps] == '#') {
                                    seats[0]++;
                                    break;
                                }
                                if (layout[i][j + steps] == 'L') {
                                    seats[1]++;
                                    break;
                                }
                            }
                        }
                        // Left
                        if (dirX == -1 && dirY == 0) {
                            for (int steps = 0;  (column - steps) >= 0; steps++) {
                                if (layout[i][j - steps] != '#' && layout[i][j - steps] != 'L') {
                                    /* layout[i][j - steps] = '*'; */
                                }
                                if (layout[i][j - steps] == '#') {
                                    seats[0]++;
                                    break;
                                }
                                if (layout[i][j - steps] == 'L') {
                                    seats[1]++;
                                    break;
                                }
                            }
                        }
                        // Down
                        if (dirX == 0 && dirY == 1) {
                            for (int steps = 0; steps < (size - row - 1); steps++) {
                                if (layout[i + steps][j] != '#' && layout[i + steps][j] != 'L') {
                                    /* layout[i + steps][j] = '*'; */
                                }
                                if (layout[i + steps][j] == '#') {
                                    seats[0]++;
                                    break;
                                }
                                if (layout[i + steps][j] == 'L') {
                                    seats[1]++;
                                    break;
                                }
                            }
                        }

                        // Up
                        if (dirX == 0 && dirY == -1) {
                            for (int steps = 0; (row - steps - 1) >= 0; steps++) {
                                if (layout[i - steps][j] != '#' && layout[i - steps][j] != 'L') {
                                    /* layout[i - steps][j] = '*'; */
                                }
                                if (layout[i - steps][j] == '#') {
                                    seats[0]++;
                                    break;
                                }
                                if (layout[i - steps][j] == 'L') {
                                    seats[1]++;
                                    break;
                                }
                            }
                        }

                        // Right - Up
                        if ((dirX == 1) && (dirY == -1)) {
                            for (int stepsX = 0, stepsY = 0 ; stepsX < (width - column) && (row - stepsY - 1 >= 0); stepsX++, stepsY++) {
                                if (layout[i - stepsY][j + stepsX] != '#' && layout[i - stepsY][j + stepsX] != 'L') {
                                    /* layout[i - stepsY][j + stepsX] = '*'; */
                                }
                                if (layout[i - stepsY][j + stepsX] == '#') {
                                    seats[0]++;
                                    break;
                                }
                                if (layout[i - stepsY][j + stepsX] == 'L') {
                                    seats[1]++;
                                    break;
                                }
                            }
                        }

                        // Right - Down
                        if ((dirX == 1) && (dirY == 1)) {
                            for (int stepsX = 0, stepsY = 0 ; stepsX < (width - column) && (row + stepsY + 1 < size); stepsX++, stepsY++) {
                                if (layout[i + stepsY][j + stepsX] != '#' && layout[i + stepsY][j + stepsX] != 'L') {
                                    /* layout[i + stepsY][j + stepsX] = '*'; */
                                }
                                if (layout[i + stepsY][j + stepsX] == '#') {
                                    seats[0]++;
                                    break;
                                }
                                if (layout[i + stepsY][j + stepsX] == 'L') {
                                    seats[1]++;
                                    break;
                                }
                            }
                        }
                        // Left - Down
                        if ((dirX == -1) && (dirY == 1)) {
                            for (int stepsX = 0, stepsY = 0 ; (width - stepsX) >= 0 && (row + stepsY + 1 < size); stepsX++, stepsY++) {
                                if (layout[i + stepsY][j - stepsX] != '#' && layout[i + stepsY][j - stepsX] != 'L') {
                                    /* layout[i + stepsY][j - stepsX] = '*'; */
                                }
                                if (layout[i + stepsY][j - stepsX] == '#') {
                                    seats[0]++;
                                    break;
                                }
                                if (layout[i + stepsY][j - stepsX] == 'L') {
                                    seats[1]++;
                                    break;
                                }
                            }
                        }
                        // Left - Up
                        if ((dirX == -1) && (dirY == -1)) {
                            for (int stepsX = 0, stepsY = 0 ; (width - stepsX) >= 0 && (row - stepsY - 1 >= 0); stepsX++, stepsY++) {
                                if (layout[i - stepsY][j - stepsX] != '#' && layout[i - stepsY][j - stepsX] != 'L' ) {
                                    /* layout[i - stepsY][j - stepsX] = '*'; */
                                }
                                if (layout[i - stepsY][j - stepsX] == '#') {
                                    seats[0]++;
                                    break;
                                }
                                if (layout[i - stepsY][j - stepsX] == 'L') {
                                    seats[1]++;
                                    break;
                                }
                            }
                        }
                    }

                    if (layout[i][j] == '#')
                        seats[0]++;

                    if (layout[i][j] == 'L' && i != row && j != column)
                        seats[1]++;
                }
            }
        }
    }
    return seats;
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

    /* int cycles = 0; */
    /* int run = 1; */
    /* while (run) { */
    /*     if (runOneCycle(arr, arr_size) == 0) */
    /*         run = 0; */
    /*     cycles++; */
    /* } */

    /* printf("Cycles: %d\n", cycles); */
    /* printf("How many seats end up occupied? %d\n", countOccupiedSeats(arr, arr_size)); */
    int* t = raycast(arr, arr_size, 4, 3);
    printSeatLayout(arr, arr_size);
    printf("Occupied: %d\n", t[0]);
    printf("Empty: %d\n", t[1]);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
