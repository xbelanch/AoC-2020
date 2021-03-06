#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* #include <SDL2/SDL.h> */

#define MAXINSTRUCTIONSSIZE 2048

typedef struct _instruction {
    char action;
    int value;
} Instruction;

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
    for (int i = 0; i < size; ++i) {
        printf("Get %c:%d\n", instructions[i].action, instructions[i].value);
    }

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
