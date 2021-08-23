#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t min;
    size_t max;
} Range;

Range *range;
size_t srange;
size_t **nearby_tickets;
size_t row;
size_t sz_nearby_tickets;

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
    return (c == '\n') ? (1) : (0);
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
    char *number = malloc(sizeof(char) * 32);
    size_t snumber = 0;
    range = malloc(sizeof(Range) * 128);
    srange = 0;
    row = 1;
    nearby_tickets = (size_t**)malloc(sizeof(size_t) * 1024);
    for (size_t i = 0; i < 1024; ++i) {
        nearby_tickets[i] = (size_t*)malloc(sizeof(size_t) * 20);
    }

    sz_nearby_tickets = 0;
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
            // Oh...
        }

        if (entrySection == 2) {
            if (isDigit(c) && isNewLine(lastChar)) {
                row++;
                sz_nearby_tickets = 0;
            }

            if (isDigit(c)) {
                number[snumber++] = c;
                number[snumber] = '\0';
            } else if ((isSymbol(c, ',') && isDigit(lastChar)) ||
                       (isNewLine(c) && isDigit(lastChar))) {
                nearby_tickets[row - 2][sz_nearby_tickets++] = atoll(number);
                number[0] = '\0';
                snumber = 0;
            }
        }

        lastChar = c;
        c = getc(fp);
    }

    fclose(fp);
    return (0);
}

size_t solutionPartOne() {
    size_t solution = 0;
    size_t notinrange = 0;

    for (size_t j = 0; j < (row - 1); ++j) {
        for (size_t i = 0; i < sz_nearby_tickets; ++i) {
            // fprintf(stdout, "%lu ", nearby_tickets[j][i]);
            for (size_t k = 0; k < srange; ++k) {
                if (inRange(range[k], nearby_tickets[j][i])) {
                    break;
                } else {
                    notinrange++;
                }
            }

            if (notinrange == srange)
                solution += nearby_tickets[j][i];

            notinrange = 0;
        }
    }

    return(solution);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    char *input_file = "input.txt";
    parse_input_file(input_file);
    fprintf(stdout, "Solution for Part One: %lu\n", solutionPartOne());
    return (0);
}
