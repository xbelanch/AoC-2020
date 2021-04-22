#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

typedef struct {
    char *value;
    int t_size;
} Number;

typedef struct {
    char *name;
    int t_size;
} Var;

typedef struct {
    char *value;
    int t_size;
} Mask;

typedef struct {
    char *address;
    int t_size;
} Memory;

void deal_with_numbers(Number *number, int chr) {
    if (number->value == NULL) {
        number->value = (char*) malloc(sizeof(char) * 32);
        number->t_size = 0;
    }
    number->value[number->t_size++] = chr;
}

void deal_with_vars(Var *variable, int chr) {
    if (variable->name == NULL) {
        variable->name = (char*) malloc(sizeof(char) * 32);
        variable->t_size = 0;
    }
    variable->name[variable->t_size++] = chr;

}

void deal_with_mask(Mask *mask, int chr) {
    if (mask->value == NULL) {
        mask->value = (char*) malloc(sizeof(char) * 32);
        mask->t_size = 0;
    }
    mask->value[mask->t_size++] = chr;
}

void deal_with_memory(Memory *memory, int chr) {
    if (memory->address == NULL) {
        memory->address = (char*) malloc(sizeof(char) * 32);
        memory->t_size = 0;
    }
    memory->address[memory->t_size++] = chr;
}

int solve_file(char *filename) {
    printf("Input file: %s\n", filename);
    FILE *fp = fopen(filename, "rb");

    assert(fp && "Input file is needed to work, bro");

    int chr;
    int is_mask;
    int line = 0;
    int rbracket = 0;
    int lbracket = 0;

    Number number = {0};
    Var variable = {0};
    Mask mask = {0};
    Memory memory = {0};

    printf("%d: ", line);
    while (1) {
        chr = fgetc(fp);

        if (chr == EOF)
            break;

        // if (chr != ' ') {
        //     printf("%c", chr);
        // }

        if (chr == '=') {
            if (strcmp(variable.name, "mask") == 0)
                is_mask = 1;
        }

        if (chr == '[')
            rbracket = 1;

        if (chr == ']') {
            rbracket = 0;
            lbracket = 1;
        }

        if (chr >= '0' && chr <= '9' && rbracket)
            deal_with_memory(&memory, chr);

        if (chr >= '0' && chr <= '9' && lbracket)
            deal_with_numbers(&number, chr);

        if (chr == '0' || chr == 'X' || chr == '1' && is_mask)
            deal_with_mask(&mask, chr);


        if (chr >= 'a' && chr <= 'z')
            deal_with_vars(&variable, chr);

        if (chr == '\n' || chr == '\r') {
            printf("%d: ", line);

            if (strcmp(variable.name, "mem") == 0) {
                printf("memory at addres %s equals to %s\n", memory.address, number.value);
            }

            if (strcmp(variable.name, "mask") == 0) {
                printf("mask equals to %s\n", mask.value);
            }

            // reset struct variables
            variable = (Var){0};
            mask = (Mask){0};
            memory = (Memory){0};
            number = (Number){0};
            is_mask = 0;
            lbracket = 0;
            rbracket = 0;

            ++line;
        }
    }
    fclose(fp);
    return (1);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
