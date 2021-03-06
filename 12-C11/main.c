#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
/* #include <SDL2/SDL.h> */

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
    int position[4]; // north, east, south, west
    int direction;
} Ship;


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

    // Print parsed input file
    /* for (int i = 0; i < size; ++i) { */
    /*     printf("Get %c:%d\n", instructions[i].action, instructions[i].value); */
    /* } */

    // Ship starts by facing 'east'
    Ship ship = {.position = {0, 0, 0, 0}, .direction = EAST};

    for (int i = 0; i < size; ++i) {
        doAction(&ship, instructions[i]);
    }

    // Print ship position
    printf("Ship position N:%d, S:%d, E:%d, W:%d\n",
           ship.position[NORTH],
           ship.position[SOUTH],
           ship.position[EAST],
           ship.position[WEST]
           );

    // Print the solution
    int solution = abs(ship.position[NORTH] - ship.position[SOUTH]) + abs(ship.position[EAST] - ship.position[WEST]);

    printf("Solution for first Day: %d\n", solution);

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
