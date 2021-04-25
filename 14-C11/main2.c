#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

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
                uintmax_t num_address =strtoimax(memory.address, NULL, 10);
                if (num_address == UINT64_MAX && errno == ERANGE)
                    return (0);

                uintmax_t num_value = strtoimax(number.value, NULL, 10);
                if (num_value == UINT64_MAX && errno == ERANGE)
                    return (0);

                printf("memory at addres %ju equals to %ju\n", num_address, num_value);
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

// The bitmask is always given as a string of 36 bits
#define bitmask_t_size 36
int number_in_binary_format[bitmask_t_size] = {0};

int numb10_to_numb2(int64_t num) {
    int b, i = 0;
    while (num != 0) {
        b = num % 2;
        num = num / 2;
        number_in_binary_format[i] = b;
        i++;
    }
    return (0);
}

int64_t numb2_to_numb10(int *num) {
    uint64_t decimal = 0, i = 0, rem;
    while (i < bitmask_t_size - 1) {
        rem = num[i] % 10;
        num[i] /= 10;
        decimal += rem * pow(2, i);
        ++i;
    }
    return decimal;
}

int apply_mask(char *mask) {
    printf("Apply mask: %s\n", mask);
    for (int i = bitmask_t_size - 1; i >= 0; --i) {
        if (mask[i] != 'X') {
            number_in_binary_format[bitmask_t_size - i - 1] =  mask[i] - '0';
        }
    }
    return (0);
}


int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        // solve_file(argv[i]);
    }

    numb10_to_numb2(101);

    printf("Number in binary format: ");
    for (int i = bitmask_t_size - 1; i >= 0; --i) {
        printf("%d", number_in_binary_format[i]);
    }

    printf("\n");
    apply_mask("XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X");

    printf("Number in binary format: ");
    for (int i = bitmask_t_size - 1; i >= 0; --i) {
        printf("%d", number_in_binary_format[i]);
    }

    int64_t num = numb2_to_numb10(number_in_binary_format);
    printf("\nBinary to base 10: %llu\n", num);

    return 0;
}
