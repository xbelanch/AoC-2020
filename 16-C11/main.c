#include <stdio.h>
#include <stdlib.h>

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
    while (c != EOF) {
        if (isNumber(lastc) && c == '\n') {
            fprintf(stdout, "\n");
            cursor = 0;
            colon = 0;
            lines++;
        } else if (cursor >= 8 && lastc == 't' && c == ':') {
            fprintf(stdout, "---\n");
        } else if (cursor >= 10 && lastc == 's' && c == ':') {
            fprintf(stdout, "---\n");
        } else if (isNumber(c)) {
            fprintf(stdout, "%c", c);
        } else if (c == '-') {
            fprintf(stdout, "%c", c);
        } else if (c == ',') {
            fprintf(stdout, "%c", c);
        } else if (colon && lastc == 'o' && c == 'r') {
            fprintf(stdout, " || ");
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

    fprintf(stdout, "\nNumber of lines: %lu\n", lines);
    fclose(fp);

    return 0;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        parse_file(argv[i]);
    }

    return 0;
}
