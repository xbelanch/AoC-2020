#include <stdio.h>
#include <stdlib.h>

void parseInput(char *filename)
{
    printf("Input filename: %s\n", filename);
    // Open, Read and close the input file
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(-1);
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        // print first number
        printf("%c", ch);
        if (ch == '\n') break;
    }

    fclose(fp);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        parseInput(argv[i]);
    };

    return 0;
}
