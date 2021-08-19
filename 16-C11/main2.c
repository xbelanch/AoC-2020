#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t min;
    size_t max;
} Range;

Range *range;
size_t srange;

int isDigit(char c) {
    return (c >= '0' && c <= '9') ? (1) : (0);
}

int isSymbol(char c, char symbol) {
    return (c == symbol) ? (1) : (0);
}

int isSpace(char c) {
    return (c == 32) ? (1) : (0);
}

int isNewLine(char c) {
    return (c == '\n' || c == '\r') ? (1) : (0);
}

int isCharacter(char c) {
    return (c == 'y' && c <= 'n') ? (1) : (0);
}

int inRange(Range range, size_t num) {
    return (num >= range.min && num <= range.max ) ? (1) : (0);
}

int parse_input_file(char *filename) {
    fprintf(stdout, "Input file: %s\n", filename);

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stdout, "ERROR: Input file %s not found!\n", filename);
        return (1);
    }

    int c = getc(fp);
    int lastChar = 0;
    size_t entrySection = 0;
    char *number = malloc(sizeof(32));
    size_t snumber = 0;
    range = malloc(sizeof(Range) * 128);
    srange = 0;
    while (c != EOF) {
        if (isNewLine(c) && isNewLine(lastChar))
            entrySection++;

        // Get only the range values from input file
        if (entrySection == 0) {
            if (isDigit(c)) {
                number[snumber] = c;
                snumber++;
                number[snumber] = '\0';
            } else if (isSymbol(c, '-') && isDigit(lastChar)) {
                range[srange].min = atoll(number);
                number[0] = '\0';
                snumber = 0;
            } else if (isSpace(c) && isDigit(lastChar)) {
                range[srange].max = atoll(number);
                number[0] = '\0';
                snumber = 0;
                srange++;
            } else if (isNewLine(c) && isDigit(lastChar)) {
                range[srange].max = atoll(number);
                number[0] = '\0';
                snumber = 0;
                srange++;
            }
        }

        if (entrySection == 1) {

        }

        if (entrySection == 2) {

        }

        lastChar = c;
        c = getc(fp);
    }

    // Print all the collected ranges
    fprintf(stdout, "srange: %lu\n", srange);
    for (size_t i = 0; i < srange; ++i) {
        fprintf(stdout, "min: %lu max: %lu\n", range[i].min, range[i].max);
    }


    fclose(fp);
    return (0);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    char *input_file = "input.txt";
    parse_input_file(input_file);

    return (0);
}
