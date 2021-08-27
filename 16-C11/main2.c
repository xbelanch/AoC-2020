#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helper.h"

typedef struct {
    size_t min;
    size_t max;
} Range;

typedef struct {
    char* name;
    Range ranges[2];
    int hasMatched;
    size_t index;
} Field;

typedef struct {
    Field *fields;
    size_t len;
} Rule;

typedef struct {
    size_t *numbers;
    size_t len;
    size_t row;
    int isInvalid;
} Ticket;

typedef struct {
    Ticket *ticket;
    size_t len;
} Nearby;

InputTextFile inputTextFile;
Rule rule;
Ticket myTicket;
Nearby nearby;

int inRange(Range range, size_t number) {
    return (number >= range.min && number <= range.max) ? (1) : (0);
}

int parse_ranges_field(Field *field, char *input) {
    int last;
    size_t range = 0;
    size_t minmatch, maxmatch;
    size_t input_len = strlen(input);
    field->name = (char*)malloc(sizeof(char) * 128);
    char *number = malloc(sizeof(char) * 16);
    size_t len = 0;
    for (size_t i = 0; i < input_len; ++i) {
        // putchar(input[i]);
        if (isSymbol(input[i], ':')) {
            memcpy(field->name, input, i);
            field->name[i] = '\0';
        }
        if (isDigit(input[i]) && isSpace(last)) minmatch = 1;
        if (isDigit(input[i]) && isSymbol(last, '-')) maxmatch = 1;
        if (isDigit(input[i]) && minmatch) number[len++] = input[i];
        if (isDigit(input[i]) && maxmatch) number[len++] = input[i];

        if (isSymbol(input[i], '-') && minmatch) {
            field->ranges[range].min = atoll(number);
            len = 0;
            minmatch = 0;
        }
        if ((isSpace(input[i]) || i == input_len - 1) && maxmatch) {
            field->ranges[range++].max = atoll(number);
            len = 0;
            maxmatch = 0;
        }

        last = input[i];
    }

    return(0);
}

int parse_Ticket(Ticket *myTicket, char *input) {
    myTicket->numbers = (size_t*)malloc(sizeof(size_t) * 128);
    myTicket->len = 0;
    size_t len_input = strlen(input);
    char *number = (char*)malloc(sizeof(char) * 32);
    size_t len = 0;
    for (size_t i = 0; i < len_input; ++i) {
        if (isDigit(input[i])) number[len++] = input[i];
        if (isSymbol(input[i], ',') || i == len_input - 1) {
            number[len] = '\0';
            myTicket->numbers[myTicket->len++] = atoll(number);
            len = 0;
        }
    }
    return (0);
}

int print_field_ranges(Rule rule, size_t i) {
    fprintf(stdout, "%s: %lu-%lu %lu-%lu", rule.fields[i].name,
            rule.fields[i].ranges[0].min,
            rule.fields[i].ranges[0].max,
            rule.fields[i].ranges[1].min,
            rule.fields[i].ranges[1].max);
    return(0);
}

int parse_input_file(char *input_filename) {

    FILE *fp = fopen(input_filename, "rb");
    if (fp == NULL) {
        fprintf(stdout, "ERROR: Input file %s not found!\n", input_filename);
        return (1);
    }

    getLines(fp, &inputTextFile);
    fprintf(stdout, "lines: %lu\n", inputTextFile.size);

    rule.fields = (Field*)malloc(sizeof(Field) * 32);
    rule.len = 0;

    nearby.ticket = (Ticket*)malloc(sizeof(Ticket) * 512);
    nearby.len = 0;

    size_t row = 0;
    size_t section = 0;
    for (size_t i = 0; i < inputTextFile.size; ++i) {
        if (!strcmp("your ticket:", inputTextFile.lines[i]) || !strcmp("nearby tickets:", inputTextFile.lines[i])) {
            section++;
        } else {
            switch(section) {
            case 0:
                parse_ranges_field(&(rule.fields)[rule.len], inputTextFile.lines[i]);
                rule.fields[rule.len].index = i;
                rule.len++;
                break;
            case 1:
                parse_Ticket(&myTicket, inputTextFile.lines[i]);
                break;
            case 2:
                nearby.ticket[nearby.len].row = row;
                parse_Ticket(&(nearby.ticket[nearby.len]), inputTextFile.lines[i]);
                nearby.len += 1;
                row += 1;
                break;
            default:
                break;
            }
        }
    }

    return (0);
}

int print_parsed_data(void) {
    // Print all the field ranges
    for (size_t i = 0; i < rule.len; ++i) {
        print_field_ranges(rule, i);
        putchar('\n');
    }
    putchar('\n');

    // Print your ticket
    for (size_t i = 0; i < myTicket.len; ++i) {
        fprintf(stdout, "%lu ", myTicket.numbers[i]);
    }
    putchar('\n');
    putchar('\n');

    // Print nearby tickets
    for (size_t i = 0; i < nearby.len; ++i) {
        for (size_t j = 0; j < nearby.ticket[i].len; ++j) {
            fprintf(stdout, "%lu ", nearby.ticket[i].numbers[j]);
        }
        putchar('\n');
    }
    return (0);
}

size_t solutionPartOne() {
    size_t solution = 0;
    size_t notinrange = 0;

    for (size_t i = 0; i < nearby.len; ++i) {
        for (size_t j = 0; j < nearby.ticket[i].len; ++j) {
            for (size_t k = 0; k < rule.len; ++k) {
                if (inRange(rule.fields[k].ranges[0], nearby.ticket[i].numbers[j]) ||
                    inRange(rule.fields[k].ranges[1], nearby.ticket[i].numbers[j])) {
                        break;
                    } else {
                        notinrange++;
                    }
            }

            if (notinrange == rule.len) {
                // Numbers that not match with any range rule
                solution += nearby.ticket[i].numbers[j];
                nearby.ticket[i].isInvalid = 1;
            }

            notinrange = 0;
        }
    }
    return(solution);
}

size_t solutionPartTwo() {

    size_t solution = 0;
    // Remove invalid nearby tickets (rows)
    for (size_t i = 0; i < nearby.len; ++i) {
        if (nearby.ticket[i].isInvalid) {
            for (size_t j = i; j < nearby.len; ++j) {
                nearby.ticket[j] = nearby.ticket[j + 1];
            }
            nearby.len -= 1;
            i--;
        }
    }

    // Traverse nearby tickets by column
    size_t len_column = nearby.ticket[0].len;
    // fprintf(stdout, "column len: %lu\n", len_column);
    // fprintf(stdout, "rule len: %lu\n", rule.len);
    // fprintf(stdout, "nearby len: %lu\n", nearby.len);

    size_t inrange = 0;
    for (size_t column = 0; column < len_column; ++column) {
        for (size_t k = 0; k < rule.len; ++k) {
            for (size_t i = 0; i < nearby.len; ++i) {
                // fprintf(stdout, "%lu ", nearby.ticket[i].numbers[column]);
                if (inRange(rule.fields[k].ranges[0], nearby.ticket[i].numbers[column]) ||
                    inRange(rule.fields[k].ranges[1], nearby.ticket[i].numbers[column])) {
                    inrange++;
                } else {
                }
            }

            if (inrange == nearby.len && !rule.fields[k].hasMatched) {
                // Numbers that match with all range ticket rule
                // fprintf(stdout, "%s", rule.fields[k].name);
                rule.fields[k].index = column;
                rule.fields[k].hasMatched = 1;
                break;
            }

            inrange = 0;
        }
    }

    solution += myTicket.numbers[rule.fields[0].index];
    for (size_t i = 1; i < 6; ++i) {
        // fprintf(stdout, "%s at %lu: %lu ... %lu", rule.fields[i].name, rule.fields[i].index, myTicket.numbers[rule.fields[i].index], solution);
        // putchar('\n');
        solution *= myTicket.numbers[rule.fields[i].index];
    }

    return (solution);

}

/*
 * Tsoding Solution:
 * Part 1: 23925
 * Part 2:
964373157673
1351393080613
 */

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    char *input_filename = "tsoding.txt";
    parse_input_file(input_filename);
    // print_parsed_data();
    fprintf(stdout, "Solution for part One: %lu\n", solutionPartOne());
    fprintf(stdout, "Solution for part Two: %lu\n", solutionPartTwo());
    return (0);
}
