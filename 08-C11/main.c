#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXSIZELINES 1024

typedef enum opcode {
    NOP = 0,
    JMP = 1,
    ACC = 2
} OPCODE;

typedef struct instruction {
    int index;
    OPCODE operation;
    int argument;
    int visited;
    struct instruction *next;
} Instruction;

typedef struct console {
    Instruction *boot;
    Instruction *instructions;
    int size;
    int accumulator;
    int index;
    int count;
} Console;

Console console; // Global, pog

void initConsole() {
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

    // store the result
    // sure there's another jai way
    for (int i = 0; buffer[i] != NULL; i++) {
        if (i == 0) {
            char* opcode = buffer[i];
            if (strcmp(opcode, "nop") == 0) {
                instruction->operation = NOP;
            } else if (strcmp(opcode,  "acc") == 0) {
                instruction->operation = ACC;
            } else if (strcmp(opcode, "jmp") == 0) {
                instruction->operation = JMP;
            } else {
                fprintf(stderr, "Unknow opcode: %s\n", opcode);
                exit(1);
            }
        } else {
            instruction->argument = atoi(buffer[i]);
        }
    }

    return instruction;
}

Instruction *getInstructionByIndex(int index) {
    Instruction *current = console.boot;

    while (current != NULL) {
        if (current->index == index)
            return current;
        current = current->next;
    }
    return NULL;
}

char *translateInstruction(int value) {
    switch(value) {
    case NOP: return "NOP";
    case JMP: return "JMP";
    case ACC: return "ACC";
    default: return NULL;
    }
}

int executeInstruction(Instruction *instruction) {

    if (!instruction->visited) {
        instruction->visited = 1;
    } else {
        /* printf("last instruction: %d>%s : %d\n", instruction->index, translateInstruction(instruction->operation), instruction->argument); */
        return 1;
    }

    switch(instruction->operation) {
    case NOP:
        console.index++;
        break;
    case ACC:
        console.accumulator += instruction->argument;
        console.index++;
        break;
    case JMP:
        console.index += instruction->argument;
        break;
    default:
        break;
    }

    /* printf("%d>%s %d | %d\n", instruction->index, translateInstruction(instruction->operation), instruction->argument, console.count); */

    console.count++;

    if (console.index >= (console.size - 1))
        return 99;

    return 0;
}

int repairConsole() {

    int stop = 0;
    int cycles = 0;
    console.index = 0;
    console.count = 1;
    console.accumulator = 0;

    // need to unvisited all operations
    for (Instruction *str = console.boot; str != NULL; str = str->next)
        str->visited = 0;


    // collected all NOPs force brute!
    for (Instruction *ptr = console.boot; ptr != NULL; ptr = ptr->next) {
        if (ptr->operation == NOP) {
            ptr->operation = JMP;
            while (!stop) {
                stop = executeInstruction(getInstructionByIndex(console.index++));
                cycles++;

                if (stop == 99) {
                    // execute last instruction
                    executeInstruction(getInstructionByIndex(console.index++));
                    return 0;
                }
            }
            /* printf("!!%d>%s %d\n", ptr->index, translateInstruction(ptr->operation), ptr->argument); */
            ptr->operation = NOP;
        }
        console.index = 0;
        console.count = 1;
        console.accumulator = 0;
        stop = 0;
        cycles = 0;
    }

    /* // Reset console */
    console.index = 0;
    console.count = 1;
    console.accumulator = 0;
    stop = 0;
    cycles = 0;
    // Need to unvisited all operations!
    for (Instruction *str = console.boot; str != NULL; str = str->next)
        str->visited = 0;

    // collected all JMPs force brute!
    for (Instruction *ptr = console.boot; ptr != NULL; ptr = ptr->next) {
        if (ptr->operation == JMP) {
            /* printf("%d>%s %d\n", ptr->index, translateInstruction(ptr->operation), ptr->argument); */
            ptr->operation = NOP;
            while (!stop) {
                stop = executeInstruction(getInstructionByIndex(console.index));
                cycles++;
                if (stop == 99) {
                    // execute last instruction
                    executeInstruction(getInstructionByIndex(console.index++));
                    return 0;
                };
            }

            ptr->operation = JMP;
        }
        // Reset console
        console.index = 0;
        console.count = 1;
        console.accumulator = 0;
        stop = 0;
        cycles = 0;
        // Need to unvisited all the operations!
        for (Instruction *str = console.boot; str != NULL; str = str->next)
            str->visited = 0;
    }
    return 0;
}

void runConsole() {
    console.index = 0;
    console.count = 1;
    console.accumulator = 0;

    int stop = 0;
    int cycles = 0;
    while (!stop) {
        stop = executeInstruction(getInstructionByIndex(console.index));
        cycles++;
    }

    printf("Console index: %d, accumulator: %d, cycles: %d\n", console.index, console.accumulator, cycles);
}

void readInput(char *filepath) {

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


    fclose(fp);
}

int solvePartOne(char *filepath) {
    printf("Input file: %s\n", filepath);
    readInput(filepath);
    initConsole();
    runConsole();
    return console.accumulator;
}

int solvePartTwo(char *filepath) {
    printf("Input file: %s\n", filepath);
    readInput(filepath);
    initConsole();
    repairConsole();
    return console.accumulator;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        assert(argc > 1);
        int solution = solvePartOne(argv[i]);
        printf("Solution for the part one of Day 8: %d\n", solution);
        solution = solvePartTwo(argv[i]);
        printf("Solution for the part two of Day 8: %d\n", solution);
    }
    return 0;
}
