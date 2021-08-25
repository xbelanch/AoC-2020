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
} Field;

typedef struct {
    Field *fields;
    size_t len;
} Rule;

typedef struct {
    size_t *numbers;
    size_t len;
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
    return number >= range.min && number <= range.max ? (1) : (0);
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
        if (isSymbol(input[i], ':')) memcpy(field->name, input, i);
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
            myTicket->numbers[myTicket->len++] = atoll(number);
            number[len - 1] = '\0';
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

    size_t section = 0;
    for (size_t i = 0; i < inputTextFile.size; ++i) {
        if (!strcmp("your ticket:", inputTextFile.lines[i]) || !strcmp("nearby tickets:", inputTextFile.lines[i])) {
            section++;
        } else {
            switch(section) {
            case 0:
                parse_ranges_field(&(rule.fields)[rule.len], inputTextFile.lines[i]);
                rule.len++;
                break;
            case 1:
                parse_Ticket(&myTicket, inputTextFile.lines[i]);
                break;
            case 2:
                parse_Ticket(&(nearby.ticket[nearby.len++]), inputTextFile.lines[i]);
                break;
            default:
                break;
            }
        }
    }


    return (0);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    char *input_filename = "input.txt";
    parse_input_file(input_filename);
    print_parsed_data();

    return (0);
}
