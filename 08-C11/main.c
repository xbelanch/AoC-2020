#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXSIZELINES 1024

typedef struct instruction {
    int index;
    char *operation;
    int argument;
    int visited;
    struct instruction *next;
} Instruction;

typedef struct console {
    Instruction *boot;
    Instruction *instructions;
    int size;
    int accumulator;
} Console;


Console console; // Global, pog

void initConsole() {
    console.accumulator = 0;
    console.instructions = (Instruction*) malloc(sizeof(Instruction));
}

Instruction *getInstructions(char *line) {
    char **buffer = NULL;
    char seps[] = " ";
    char *token;
    int nspaces = 0;
    Instruction *instruction = malloc(sizeof(Instruction));
    instruction->visited = 0;
    instruction->next = NULL;

    token = strtok(line, seps);

    while (token) {
        buffer = realloc(buffer, sizeof(char*) * ++nspaces);

        assert(buffer != NULL);

        buffer[nspaces - 1] = token;
        token = strtok(NULL, seps);
    }

    buffer = realloc(buffer, sizeof(char*) * (nspaces + 1));
    buffer[nspaces] = 0;

    // print the result
    for (int i = 0; buffer[i] != NULL; i++) {
        if (i == 0) {
            instruction->operation = buffer[i];
        } else {
            instruction->argument = atoi(buffer[i]);
        }
    }


    return instruction;
}

void readInput(char *filepath) {
    printf("Input file: %s\n", filepath);

    FILE *fp = fopen(filepath, "rb");

    if (fp == NULL) {
        perror("Failed: ");
        exit(0);
    }

    char lines[MAXSIZELINES] = "";

    console.instructions = NULL;
    int index = 0;
    while (fgets(lines, sizeof(lines), fp) != NULL) {
        if (console.instructions == NULL ) {
            console.instructions = (Instruction*) malloc(sizeof(Instruction));
            console.instructions = getInstructions(lines);
            console.instructions->next = NULL;
            console.instructions->index = index;
            console.boot = console.instructions;
            index++;
        } else {
            Instruction *tmp = (Instruction*) malloc(sizeof(Instruction));
            tmp = getInstructions(lines);
            tmp->index = index;
            tmp->next = NULL;
            console.instructions->next = tmp;
            console.instructions = tmp;
            index++;
        }
    }

    console.size = index;
    // print console boot code
    for (Instruction *ptr = console.boot ; ptr != NULL; ptr = ptr->next) {
        printf("instruction[%d]: %s %d\n", ptr->index, ptr->operation, ptr->argument);
    }

    fclose(fp);
}

int solvePartOne(char *filepath) {
    initConsole();
    readInput(filepath);

    return 0;
}


int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        assert(argc > 1);
        int solution = solvePartOne(argv[i]);
        printf("Solution for the part one of Day 8: %d\n", solution);
    }
    return 0;
}
