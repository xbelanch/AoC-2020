#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    FILE *file;
    int Lines;
    int Putcharback;
} InputFile;

InputFile inputfile = {0};

int next(void){
    int chr;

    chr = fgetc(inputfile.file);
    if (chr == '\n')
        inputfile.Lines++;

    return chr;
}

int skip(void) {
    int chr;
    chr = next();
    while (chr == ' ' ||
           chr == '\n' ||
           chr == '\t' ||
           chr == '\r' ||
           chr == '\f') {
        chr = next();
    }

    return (chr);
}

int scan(void) {
    int chr;

    // Skip whitespace
    chr = skip();

    switch (chr) {
    case EOF:
        return (0);
    default:
        printf("%c", chr);
    }

    return (1);
}


int solve_file(char* filename) {
    printf("Filename: %s\n", filename);

    inputfile.file = fopen(filename, "r");

    while (scan()) {

    }

    fclose(inputfile.file);
    return (1);
}

int logInputFile(void){
    fprintf(stdout, "Lines: %d\n", inputfile.Lines);
    return (0);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
        // Print some info from input files
        logInputFile();
        // reset input file struct
        inputfile = (InputFile){0};

    }

    return (0);
}
