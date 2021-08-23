#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *fieldname;
    size_t sz_fieldname;
    size_t position;
    size_t *ranges;
    size_t sz_ranges;
    int match;
} Range;

Range *range;
size_t srange;
size_t **nearby_tickets;
size_t row;
size_t sz_nearby_tickets;
size_t *myticket;
size_t sz_myticket;

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
    return (c >= 'a' && c <= 'z') ? (1) : (0);
}

int inRange(Range range, size_t num) {
    return ((num >= range.ranges[0] && num <= range.ranges[1]) ||
            (num >= range.ranges[2] && num <= range.ranges[3])) ? (1) : (0);
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
    range[srange].ranges = (size_t*) malloc(sizeof(size_t) * 128);
    range[srange].sz_ranges = 0;
    range[srange].position = 0;
    range[srange].fieldname = (char*)malloc(sizeof(char) * 512);
    range[srange].sz_fieldname = 0;
    range[srange].match = 0;


    row = 1;
    nearby_tickets = (size_t**)malloc(sizeof(size_t) * 1024);
    for (size_t i = 0; i < 1024; ++i) {
        nearby_tickets[i] = (size_t*)malloc(sizeof(size_t) * 20);
    }
    sz_nearby_tickets = 0;
    myticket = (size_t*)malloc(sizeof(size_t) * 32);
    sz_myticket = 0;

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
                range[srange].ranges[range[srange].sz_ranges++] = atoll(number);
                number[0] = '\0';
                snumber = 0;
            } else if (isSpace(c) && isDigit(lastChar)) {
                range[srange].ranges[range[srange].sz_ranges++] = atoll(number);
                number[0] = '\0';
                snumber = 0;
            } else if (isNewLine(c) && isDigit(lastChar)) {
                range[srange].ranges[range[srange].sz_ranges++] = atoll(number);
                number[0] = '\0';
                snumber = 0;
                range[srange].position = srange;
                srange++;

                range[srange - 1].fieldname[range[srange - 1 ].sz_fieldname] = '\0';
                range[srange].fieldname = (char*)malloc(sizeof(char) * 128);
                range[srange].sz_fieldname = 0;
                range[srange].ranges = (size_t*)malloc(sizeof(size_t) * 128);
                range[srange].sz_ranges = 0;
                range[srange].match = 0;

            } else if ((isCharacter(c) || (isSpace(c))) &&
                       !(c == 'o' && (isSpace(lastChar))) &&
                       !(c == 'r' && lastChar == 'o'))
                {
                range[srange].fieldname[range[srange].sz_fieldname] = c;
                range[srange].sz_fieldname++;
            }
        }

        if (entrySection == 1) {
            // ... do something myticket
            if (isDigit(c)) {
                number[snumber++] = c;
                number[snumber] = '\0';
            } else if ((isSymbol(c, ',')) && (isDigit(lastChar))) {
                myticket[sz_myticket] = atoll(number);
                number[0] = '\0';
                snumber = 0;
                sz_myticket++;
            } else if (isNewLine(c) && isDigit(lastChar)) {
                myticket[sz_myticket] = atoll(number);
                number[0] = '\0';
                snumber = 0;
                sz_myticket++;
            }
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

size_t solutionPartTwo() {
    size_t solution = 0;
    size_t match[srange];
    // reset match
    for (size_t k = 0; k < srange; ++k) {
        match[k] = 0;
    }

    size_t i, j, column;
    for (column = 0; column < sz_nearby_tickets; ++column) {
        for (j = 0; j < (row - 1); ++j) {
            for (i = 0; i < srange; ++i) {
                if (inRange(range[i], nearby_tickets[j][column])) {
                    // fprintf(stdout, "ticket %lu match with %s\n", nearby_tickets[j][column], range[i].fieldname);
                    match[i]++;
                }
            }
        }
        // printf("----\n");
        for (size_t k = 0; k < srange; ++k) {
            // fprintf(stdout, "%s has %lu hits\n", range[k].fieldname, match[k]);
            if (match[k] == (row - 1) && !range[k].match) {
                fprintf(stdout, "%s\n", range[k].fieldname);
                range[k].match = 1;
            }
        }
        // reset match
        for (size_t k = 0; k < srange; ++k) {
            match[k] = 0;
        }
    }

    return solution;
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
    // fprintf(stdout, "Solution for Part One: %lu\n", solutionPartOne());
    fprintf(stdout, "Solution for Part Two: %lu\n", solutionPartTwo());
    return (0);
}
