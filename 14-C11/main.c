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

int mask_value_op(char *mask, size_t value) {
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
    fprintf(stdout, "New value: %lu\n", value);
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

    // Testing area
    parse_input_file(nline);
    mask_value_op(lines[0].mask, 0);
    mask_value_op(lines[0].mask, 101);
    mask_value_op(lines[0].mask, 11);
    mask_value_op("00000X110010111111X000100XX01010000X", 231);
    mask_value_op("00000X110010111111X000100XX01010000X", 435);

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
