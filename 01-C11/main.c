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
    char cnumber[4];
    int inumber;
    int i = 0;

    while ((ch = fgetc(fp)) != EOF) {
        // print first number
        if (ch == '\n') break;
        cnumber[i] = ch;
        i++;
    }

    cnumber[4] = '\0';

    printf("First number of the list %s as a string\n", cnumber);

    inumber = atoi(cnumber);

    printf("First number of the list %i as an integer\n", inumber);



    fclose(fp);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        parseInput(argv[i]);
    };

    return 0;
}
