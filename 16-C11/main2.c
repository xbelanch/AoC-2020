#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t min;
    size_t max;
} Range;

Range *range;

int isDigit(char c) {
    return (c >= '0' && c <= '9') ? (1) : (0);
}

int isSymbol(char c) {
    return (c == '-' || c == ',') ? (1) : (0);
}

int isSpace(char c) {
    return (c == 32) ? (1) : (0);
}

int isNewLine(char c) {
    return (c == 10) ? (1) : (0);
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
    while (c != EOF) {
        if (isDigit(c)) {
            putchar(c);
        } else if (isSymbol(c) ||
                   (isSpace(c) && isDigit(lastChar)) ||
                   (isNewLine(c) && isDigit(lastChar))) {
            putchar('\n');
        }
        lastChar = c;
        c = getc(fp);
    }

    fclose(fp);
    return (0);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    char *input_file = "sample-input.txt";
    parse_input_file(input_file);

    return (0);
}
