#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE_LINES 1024
#define BITMASK_SIZE 35

typedef struct line {
    char* text;
    char* mask;
    int addr;
    size_t value;
} Line;

Line lines[MAX_SIZE_LINES];
size_t Memory[USHRT_MAX];
int *memory_table_lookup;
int len_memory_table_lookup;

// Stolen from https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
static int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

static char *bin(size_t value) {
    char *binary = malloc(sizeof(char) * BITMASK_SIZE);
    for (int i = BITMASK_SIZE; i >= 0; --i) {
        int k = value >> i;
        binary[BITMASK_SIZE - i] = k & 1 ? '1' : '0';
    }
    return binary;
}

static size_t bin2dec(char *value) {
    size_t decimal = 0;
    for (int i = BITMASK_SIZE; i >= 0; --i) {
        if (value[i] == '1') {
            decimal += 1UL << (BITMASK_SIZE - i);
        }
    }
    return decimal;
}

static char *bitmask_op(char* mask, char *value) {
    for (int i = BITMASK_SIZE; i >= 0; --i) {
        if (mask[BITMASK_SIZE - i] != 'X')
            value[BITMASK_SIZE - i] = mask[BITMASK_SIZE - i];
    }
    return value;
}

int log_memory_table_lookup() {
    for (int i = 0; i < len_memory_table_lookup; ++i) {
        int addr = memory_table_lookup[i];
        fprintf(stdout, "[%d]= %lu\n", addr, Memory[addr]);
    }
    return 0;
}

size_t partOne(int size_lines) {
    char *mask = 0;
    size_t solution = 0;
    for (int i = 0; i < size_lines; ++i) {
        if (!lines[i].mask) {
            char *binary = bin(lines[i].value);
            char *bitmasked_value = bitmask_op(mask, binary);
            size_t value = bin2dec(bitmasked_value);
            Memory[lines[i].addr] = value;
        } else {
            mask = lines[i].mask;
        }
    }
    for (int i = 0; i < len_memory_table_lookup; ++i) {
        solution += Memory[memory_table_lookup[i]];
    }
    // log_memory_table_lookup();
    return solution;
}

void perm_address(char *mask, size_t value) {
    // check how floating bits the mask have
    int floating_bits_count = 0;
    for (int i = BITMASK_SIZE; i >= 0 ; --i) {
        if (mask[i] == 'X')
            floating_bits_count++;
    }

    // no floating bits?
    if (0 == floating_bits_count)
        return 0;

    // set the max number of mask permutations
    int max_perms = 1 << floating_bits_count;
    printf("max_perms: %d\n", max_perms);
    char *perms[max_perms];
    for (int i = 0; i < max_perms; ++i)
        perms[i] = malloc(sizeof(char) * BITMASK_SIZE);

    char *variations[max_perms];
    // TODO: Implement permutations of '1' and '0' of floating bits size
    variations[0] = "00";
    variations[1] = "01";
    variations[2] = "10";
    variations[3] = "11";

    char *last = malloc(sizeof(char)* BITMASK_SIZE);
    last = mask;

    int idx = 0;
    for (int i = 0; i < max_perms; ++i) {
        for (int j = BITMASK_SIZE; j >= 0; --j) {
            if (last[j] == 'X') {
                perms[i][j] = variations[i][idx];
                idx++;
            } else {
                perms[i][j] = mask[j];
            }
        }
        idx = 0;
    }

    printf("[%s]\n", mask);
    for (int i = 0; i < max_perms; ++i) {
        Memory[bin2dec(perms[i])] = value;
        printf("[%s] = %lu\n", perms[i], bin2dec(perms[i]));
    }

    return 0;
}

size_t partTwo(int size_lines) {
    size_t solution = 0;
    size_t addr = 42;
    char *mask = "000000000000000000000000000000X1001X";
    char *address = bin(addr);
    fprintf(stdout, "address: %s\n", address);
    for (int i = BITMASK_SIZE; i >= 0; --i)
        address[BITMASK_SIZE - i] = mask[BITMASK_SIZE - i] != 'X' ? mask[BITMASK_SIZE - i] | address[BITMASK_SIZE - i] : 'X';

    fprintf(stdout, "address: %s\n", address);

    // Create the stack of memory addresses due to floating bit mask (X)
    size_t max_stack_size = 128;
    int count = 0;
    char *stack = malloc(sizeof(char) * max_stack_size);

    perm_address(address, 100);
    return solution;
}

int set_memory_table_lookup(int size_lines) {
    int count = 0;
    memory_table_lookup = malloc(sizeof(int) * size_lines);

    for (int i = 0; i < size_lines; ++i) {
        if (!lines[i].mask) {
            memory_table_lookup[count] = lines[i].addr;
            count++;
        }
    }

    // Sort memory_table before we remove duplicated addresses
    qsort(memory_table_lookup, count, sizeof(int), cmpfunc);

    // Remove duplicated addresses memory values
    int *tmp = malloc(sizeof(int) * count);
    int len = 0;
    for (int i = 0; i < count; ++i) {
        if (memory_table_lookup[i] != memory_table_lookup[i + 1]) {
            tmp[len] = memory_table_lookup[i];
            len++;
        }
    }

    tmp = realloc(tmp, len * sizeof(tmp[0]));
    memory_table_lookup = realloc(memory_table_lookup, len * sizeof(tmp[0]));
    for (int i = 0; i < len; i++)
        memory_table_lookup[i] = tmp[i];

    len_memory_table_lookup = len;
    return 0;
}

int parse_input_file(int size_lines) {
    for (int i = 0; i < size_lines; ++i) {
        if (0 == strncmp(lines[i].text, "mem", 3)) {
            // Set mask to NULL
            lines[i].mask = NULL;

            // Extract memory address value
            char *p_open_bracket = strchr(lines[i].text, '[');
            char *p_close_bracket = strchr(lines[i].text, ']');
            size_t diff = p_close_bracket - p_open_bracket;
            char *mem = (char *)malloc(sizeof(char) * (diff - 1));
            char *ptr = lines[i].text + 4; // mem[
            memcpy(mem, ptr, diff - 1);
            lines[i].addr = atoi(mem);

            // Extract assigned memory value
            char *p_equal = strchr(lines[i].text, '=');
            diff = p_equal - lines[i].text;
            size_t len = strlen(lines[i].text) - (diff + 2);
            char *value = (char *)malloc(sizeof(char) * len);
            ptr = lines[i].text + diff + 2;
            memcpy(value, ptr, len);
            lines[i].value = atoll(value);

            // Assign value to memory address
            Memory[lines[i].addr] = lines[i].value;

        } else {
            // Extract mask value
            size_t len = strlen(lines[i].text) - 7;
            lines[i].mask = (char *)malloc(sizeof(char) * len);
            char *ptr = lines[i].text + 7;
            memcpy(lines[i].mask, ptr, len);
        }
    }
    fprintf(stdout, "Total number of lines: %d\n", size_lines);
    return 0;
}

int input_file(char *filename){
    int error = -1;
    printf("Open file: %s\n", filename);
    FILE *input_file = fopen(filename, "rb");

    if (NULL == input_file) {
        fprintf(stderr, "File %s didn't found!\n", filename);
        return error;
    }

    int c = fgetc(input_file);
    char* string = (char *)malloc(sizeof(char) * 512);
    size_t i = 0;
    int nline = 0;

    while (EOF != c) {
        string[i++] = c;
        if ('\n' == c) {
            string[i-1] = '\0';
            size_t len = strlen(string);
            lines[nline].text = (char *)malloc(sizeof(char) * len);
            memcpy(lines[nline].text, string, len);
            i = 0; nline++;
            string[i] = '\0';
        }
        c = fgetc(input_file);
    }

    parse_input_file(nline);
    set_memory_table_lookup(nline);
    // fprintf(stdout, "Solution part One: %lu\n", partOne(nline));
    fprintf(stdout, "Solution part One: %lu\n", partTwo(nline));

    int success = fclose(input_file);
    return success;
}


int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        input_file(argv[i]);
    }
    return 0;
}
