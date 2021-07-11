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
size_t len_memory_table_lookup;

// Stolen from https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
static int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

size_t mask_value_op(char *mask, size_t value) {
    size_t len = strlen(mask);
    for (int i = len; i >= 0; --i) {
        int pos = len - i - 1;
        if (mask[i] == '1') {
            value |= (int)pow(2, pos);
        }
        if (mask[i] == '0') {
            value -= (value & (int)pow(2, pos));
        }
    }
    // fprintf(stdout, "New value: %lu\n", value);
    return value;
}

int partOne(int size_lines) {
    char *mask = 0;
    size_t solution = 0;
    for (int i = 0; i < size_lines; ++i) {
        if (!lines[i].mask) {
            // Apply mask to assigned addresses values
            size_t value = mask_value_op(mask, lines[i].value);
            Memory[lines[i].addr] = value;
        } else {
            // Update mask
            mask = lines[i].mask;
            printf("mask: %s\n", mask);
        }
    }
    for (int i = 0; i < len_memory_table_lookup; ++i) {
        fprintf(stdout, "%lu\n", Memory[memory_table_lookup[i]]);
        solution += Memory[memory_table_lookup[i]];
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
