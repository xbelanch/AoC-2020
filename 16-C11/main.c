#include <stdio.h>
#include <stdlib.h>

int parse_file(char *filename) {
    fprintf(stdout, "Input file: %s\n", filename);

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stdout, "ERROR: Input file %s not found!\n", filename);
        return 1;
    }

    int c = getc(fp);
    size_t lines = 0;
    while (c != EOF) {
        if (c == '\n') {
            lines++;
        } else {
            // fprintf(stdout, "%c", c);
        }
        c = getc(fp);
    }

    fprintf(stdout, "Number of lines: %lu\n", lines);
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
