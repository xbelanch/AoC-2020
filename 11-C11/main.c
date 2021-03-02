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

int raycastV2(char **layout, int height, int width, int row, int column) {
    int occupied = 0;
    int x, y;

    for (int i = -1; i <= 1; i++) { // rows
        y = row + i;
        for (int j = -1; j <= 1; j++) { // columns
            x = column + j;
            if (x >= 0 && x <= width - 1 && y >= 0 && y <= height - 1) {
                if (x == column && y == row) {
                    continue;
                } else {
                    if (layout[y][x] == '#')
                        occupied += 1;

                    if (layout[y][x] == '.') {
                        // Raycast here
                        int dirX = x - column;
                        int dirY = y - row;

                        // x: 1 y: 0
                        if (dirX == 1 && dirY == 0) {
                            for (int steps = 0; steps + x <= width - 1; steps++) {
                                if (layout[y][x + steps] == 'L')
                                    break;
                                if (layout[y][x + steps] == '#') {
                                    occupied += 1;
                                    break;
                                }
                            }
                        }

                        // x: -1 y: 0
                        if (dirX == -1 && dirY == 0) {
                            for (int steps = 0; x - steps >= 0; steps++) {
                                if (layout[y][x - steps] == 'L')
                                    break;
                                if (layout[y][x - steps] == '#') {
                                    occupied += 1;
                                    break;
                                }
                            }
                        }

                        // x: 0  y: 1
                        if (dirX == 0 && dirY == 1) {
                            for (int steps = 0; y + steps <= height - 1; steps++) {
                                if (layout[y + steps][x] == 'L')
                                    break;
                                if (layout[y + steps][x] == '#') {
                                    occupied += 1;
                                    break;
                                }
                            }
                        }

                        // x: 0  y: -1
                        if (dirX == 0 && dirY == -1) {
                            for (int steps = 0; y - steps >= 0; steps++) {
                                if (layout[y - steps][x] == 'L')
                                    break;
                                if (layout[y - steps][x] == '#') {
                                    occupied += 1;
                                    break;
                                }
                            }
                        }

                        // x: 1  y: -1
                        if (dirX == 1 && dirY == -1) {
                            for (int steps = 0; y - steps >= 0 && x + steps <= width - 1; steps++) {
                                if (layout[y - steps][x + steps] == 'L')
                                    break;
                                if (layout[y - steps][x + steps] == '#') {
                                    occupied += 1;
                                    break;
                                }
                            }
                        }

                        // x: 1  y: 1
                        if (dirX == 1 && dirY == 1) {
                            for (int steps = 0; y + steps <= height - 1 && x + steps <= width - 1; steps++) {
                                if (layout[y + steps][x + steps] == 'L')
                                    break;
                                if (layout[y + steps][x + steps] == '#') {
                                    occupied += 1;
                                    break;
                                }
                            }
                        }

                        // x: -1  y: 1
                        if (dirX == -1 && dirY == 1) {
                            for (int steps = 0; y + steps <= height - 1 && x - steps >= 0; steps++) {
                                if (layout[y + steps][x - steps] == 'L')
                                    break;
                                if (layout[y + steps][x - steps] == '#') {
                                    occupied += 1;
                                    break;
                                }
                            }
                        }

                        // x: -1  y: 1
                        if (dirX == -1 && dirY == -1) {
                            for (int steps = 0; y - steps >= 0 && x - steps >= 0; steps++) {
                                if (layout[y - steps][x - steps] == 'L')
                                    break;
                                if (layout[y - steps][x - steps] == '#') {
                                    occupied += 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return occupied;
}

int checkRuleOne(char **layout, int size, int row, int column) {
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


// Print the seat layout
void printSeatLayout(char **layout, int size) {
    /* printf("Rows: %d\n", size - 1); */
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; layout[i][j]; j++) {
            printf("%c", layout[i][j]);
        }
        printf("\n");
    }
}


int runOneCycleV2(char **layout, int size) {
    char *buffer[N + 1];
    int change = 0;

    for (int i = 0; i < size - 1; i++) {
        buffer[i] = malloc(sizeof(char) * N + 1);
        strcpy(buffer[i], layout[i]);
    }

    int width = strlen(layout[0]) - 1;
    int height = size - 1;
    for (int i = 0; i <= height - 1; i++) {
        for (int j = 0; j <= width - 1; j++) {
            if (buffer[i][j] == 'L' && raycastV2(buffer, height, width, i, j) == 0) {
                layout[i][j] = '#';
                change += 1;
            }
            if (buffer[i][j] == '#' && raycastV2(buffer, height, width, i, j) >= 5) {
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


void solve_file_part_one(char *filename) {
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

    // Part One
    int cycles = 0;
    int run = 1;
    while (run) {
        if (runOneCycle(arr, arr_size) == 0)
            run = 0;
        cycles++;
    }

    printf("Solution for Part One: \n");
    printf("Cycles: %d\n", cycles);
    printf("How many seats end up occupied? %d\n", countOccupiedSeats(arr, arr_size));
}

void solve_file_part_two(char *filename) {
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

    // Part Two
    int cycles = 0;
    int run = 1;
    while (run) {
        if (runOneCycleV2(arr, arr_size) == 0)
            run = 0;
        cycles++;
    }
    printf("Solution for Part Two: \n");
    printf("Cycles: %d\n", cycles);
    printf("How many seats end up occupied? %d\n", countOccupiedSeats(arr, arr_size));
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file_part_one(argv[i]);
        solve_file_part_two(argv[i]);
    }
    return 0;
}
