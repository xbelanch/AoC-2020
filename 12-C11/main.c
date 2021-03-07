#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXINSTRUCTIONSSIZE 2048

typedef enum _action {
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
} Direction;

typedef struct _instruction {
    char action;
    int value;
} Instruction;

typedef struct _ship {
    long position[4]; // north, east, south, west
    int direction;
    int waypoint[4]; // notth, east, south, west
} Ship;

void printShipPosition(Ship ship) {
    printf("Ship position N:%ld, S:%ld, E:%ld, W:%ld\n",
           ship.position[NORTH],
           ship.position[SOUTH],
           ship.position[EAST],
           ship.position[WEST]
           );
}

void printShipWaypoint(Ship ship) {
    printf("Ship waypoint N:%d, S:%d, E:%d, W:%d\n",
           ship.waypoint[NORTH],
           ship.waypoint[SOUTH],
           ship.waypoint[EAST],
           ship.waypoint[WEST]
           );
}

void doActionV2(Ship *ship, Instruction instruction) {
    switch(instruction.action) {
    case ('N'): {
        ship->waypoint[NORTH] += instruction.value;
        break;
    }
    case ('E'): {
        ship->waypoint[EAST] += instruction.value;
        break;
    }
    case ('S'): {
        ship->waypoint[SOUTH] += instruction.value;
        break;
    }
    case ('W'): {
        ship->waypoint[WEST] += instruction.value;
        break;
    }
    case('F'): {
        for (int i = 0; i < 4; i++) {
            ship->position[i] += instruction.value * ship->waypoint[i];
        }
        break;
    }
    case('R'): {
        int t[4];
        for (int i = 0; i < 4; i++) {
            t[i] = ship->waypoint[i];
        }
        int rotate =  instruction.value / 90;
        for (int i = 0; i < 4; i++) {
            ship->waypoint[(i + rotate) % 4] = t[i];
        }
        break;
    }
    case('L'): {
        int t[4];
        for (int i = 0; i < 4; i++) {
            t[i] = ship->waypoint[i];
        }
        int rotate =  instruction.value / 90;
        for (int i = 0; i < 4; i++) {
            ship->waypoint[i] = t[(i + rotate) % 4];
        }
        break;
    }

    }
}

void doAction(Ship *ship, Instruction instruction) {
    switch(instruction.action) {
    case ('N'): {
        ship->position[NORTH] += instruction.value;
        break;
    }
    case ('S'): {
        ship->position[SOUTH] += instruction.value;
        break;
    }
    case ('E'): {
        ship->position[EAST] += instruction.value;
        break;
    }
    case ('W'): {
        ship->position[WEST] += instruction.value;
        break;
    }
    case ('F'): {
        ship->position[ship->direction] += instruction.value;
        break;
    }
    case ('R'): {
        // Need to improve this
        if (instruction.value == 90) {
            ship->direction += 1;
        } else if (instruction.value == 180) {
            ship->direction += 2;
        } else if (instruction.value == 270) {
            ship->direction += 3;
        }

        if (ship->direction >= 4)
            ship->direction %= 4;

        break;
    }
    case ('L'): {
        // Need to improve this
        if (instruction.value == 90) {
            ship->direction -= 1;
        } else if (instruction.value == 180) {
            ship->direction -= 2;
        } else if (instruction.value == 270) {
            ship->direction -= 3;
        }

        if (ship->direction < 0)
            ship->direction = 4 + (ship->direction % 4);

        break;
    }

    }
}

int partOne(Instruction *instructions, int size)
{
    /* Part One of Day 12 */
    /* Ship starts by facing 'east' */
    Ship ship = {.position = {0, 0, 0, 0}, .direction = EAST};

    for (int i = 0; i < size; ++i) {
        doAction(&ship, instructions[i]);
    }

    // Print the solution
    int solution = abs(ship.position[NORTH] - ship.position[SOUTH]) + abs(ship.position[EAST] - ship.position[WEST]);

    return solution;
}

long partTwo(Instruction *instructions, int size)
{
    /* Part One of Day 12 */
    Ship ship = { .position = {0, 0, 0, 0}, .direction = EAST, .waypoint = {1, 10, 0, 0}};
    for (int i = 0; i < size; ++i) {
        doActionV2(&ship, instructions[i]);

    }
    // Print the solution
    long solution = abs(ship.position[NORTH] - ship.position[SOUTH]) + abs(ship.position[EAST] - ship.position[WEST]);

    return solution;
}

int solve_file(const char *filename) {
    printf("Input file: %s\n", filename);
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("File opening failed\n");
        return EXIT_FAILURE;
    }
    Instruction instructions[MAXINSTRUCTIONSSIZE];
    int size = 0;

    while (!feof(fp)) {
        instructions[size] = (Instruction){0};
        fscanf(fp, "%1c%d\r\n", &instructions[size].action, &instructions[size].value);
        size += 1;
    }
    printf("lines: %d\n", size);
    // Solution for part one
    printf("Solution for part One: %d\n", partOne(instructions, size));
    // Solution for part two
    printf("Solution for part Two: %ld\n", partTwo(instructions, size));

    fclose(fp);
    return 0;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
