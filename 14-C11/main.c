#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAX_SIZE_LINES 1024

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

static char *decimal2binary(size_t value) {
    char *binary = malloc(sizeof(char) * 63);
    for (int i = 35; i >= 0; --i) {
        int k = value >> i;
        binary[35 - i] = k & 1 ? '1' : '0';
    }
    return binary;
}

static size_t binary2decimal(char *value) {
    size_t decimal = 0;
    for (int i = 35; i >= 0; --i) {
        if (value[i] == '1') {
            decimal += pow(2, 35 - i);
        }
    }
    return decimal;
}

static char *bitmask_op(char* mask, char *value) {
    for (int i = 35; i >= 0; --i) {
        if (mask[35 - i] != 'X')
            value[35 - i] = mask[35 - i];
    }
    return value;
}

int partOne(int size_lines) {
    char *mask = 0;
    size_t solution = 0;
    for (int i = 0; i < size_lines; ++i) {
        if (!lines[i].mask) {
            char *binary = decimal2binary(lines[i].value);
            printf("binary input: \t\t%s\n", binary);
            char *bitmasked_value = bitmask_op(mask, binary);
            printf("binary output: \t\t%s\n", bitmasked_value);
            size_t value = binary2decimal(bitmasked_value);
            Memory[lines[i].addr] = value;
        } else {
            // Update mask
            mask = lines[i].mask;
            printf("mask: \t\t\t\t%s\n", mask);
        }
    }
    for (int i = 0; i < len_memory_table_lookup; ++i) {
        solution += Memory[memory_table_lookup[i]];
        printf("[%d]: %lu\n", memory_table_lookup[i], Memory[memory_table_lookup[i]]);
    }

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

    // sort memory_table before we remove duplicated addresses
    qsort(memory_table_lookup, count, sizeof(int), cmpfunc);

    // Remove duplicated addresses memory values
    int *tmp = malloc(sizeof(int) * count);
    int len = 0;
    for (int i = 0; i < count -1; ++i) {
        if (memory_table_lookup[i] != memory_table_lookup[i + 1]) {
            tmp[len++] = memory_table_lookup[i];
        }
    }
    tmp[len++] = memory_table_lookup[count - 1];
    tmp = realloc(tmp, len * sizeof(tmp[0]));

    memory_table_lookup = realloc(memory_table_lookup, len * sizeof(tmp[0]));
    for (int i = 0; i < len; i++)
        memory_table_lookup[i] = tmp[i];

    len_memory_table_lookup = len;
    return 0;
}

int parse_input_file(int size_lines) {
    for (int i = 0; i < size_lines; ++i) {
        // fprintf(stdout, "%u: %s\n", i, lines[i].text);

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
    size_t solution = partOne(nline);
    fprintf(stdout, "Solution part One: %lu\n", solution);

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
