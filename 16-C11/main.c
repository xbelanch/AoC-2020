#include <stdio.h>
#include <stdlib.h>

size_t ranges[1024][2];
size_t *buffer;

int isNumber(char c) {
    return (c >= '0' && c <= '9') ? 1 : 0;
}

int parse_file(char *filename) {
    fprintf(stdout, "Input file: %s\n", filename);

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stdout, "ERROR: Input file %s not found!\n", filename);
        return 1;
    }

    int c = getc(fp);
    int lastc = c;
    size_t cursor = 0;
    size_t colon = 0;
    size_t lines = 0;
    char *number = malloc(sizeof(char) * 64);
    size_t digit = 0;
    size_t numbers[128];
    size_t snumbers = 0;
    int inRange = 1;
    int inTickets = 0;
    size_t maxRange = 0;
    while (c != EOF) {
        if (isNumber(lastc) && c == '\n') {
            fprintf(stdout, "\n");
            cursor = 0;
            colon = 0;
            lines++;

            if (inRange) {
                numbers[snumbers] = atoll(number);
                digit = 0;
                number[digit] = '\0';
                snumbers++;
            }

        } else if (cursor >= 8 && lastc == 't' && c == ':') {
            inRange = 0;
            inTickets++;
            fprintf(stdout, "---\n");
        } else if (cursor >= 10 && lastc == 's' && c == ':') {
            inRange = 0;
            inTickets++;
            fprintf(stdout, "---\n");
        } else if (isNumber(c)) {

            fprintf(stdout, "%c", c);
            number[digit] = c;
            digit++;

        } else if (c == '-') {

            if (inRange) {
                fprintf(stdout, "%c", c);
                numbers[snumbers] = atoll(number);
                digit = 0;
                number[digit] = '\0';
                snumbers++;
            }

        } else if (c == ',') {
            fprintf(stdout, "%c", c);
        } else if (colon && lastc == 'o' && c == 'r') {

            if (inRange) {
                fprintf(stdout, " || ");
                numbers[snumbers] = atoll(number);
                digit = 0;
                number[digit] = '\0';
                snumbers++;
            }

        } else if (c == ':') {
            colon = 1;
        } else if (c == '\n') {
            cursor = 0;
            lines++;
        } else {

        }
        cursor++;
        lastc = c;
        c = getc(fp);
    }

    // print the ranges
    for (size_t i = 0; i < snumbers - 1; ++i) {
        for (size_t j = numbers[i]; j <= numbers[i + 1]; j++) {
            buffer[j] = j;
        }
        ++i;
    }

    // for (size_t i = 0; i < 51; ++i)
    //     fprintf(stdout, "%lu: %lu\n", i, buffer[i]);

    size_t result = 0;
    for (size_t i = 0; i < 50; ++i) {
        if (buffer[i] != i) {
            result += i;
        }
    }

    fprintf(stdout, "Result: %lu\n", result + 55);
    fclose(fp);

    return 0;
}

int main(int argc, char *argv[])
{

    buffer = malloc(sizeof(size_t) * 30 * 1000 * 1000);
    for (size_t i = 0; i < 30 * 1000 * 1000; ++i)
        buffer[i] = -1;

    for (int i = 1; i < argc; ++i) {
        parse_file(argv[i]);
    }

    return 0;
}
