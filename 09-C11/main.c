#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXSIZELINE 512
#define MAXSIZELINES 2048

unsigned long long int numbers[MAXSIZELINES];

void solveFile(char *filePath) {
    FILE *fp = fopen(filePath, "rb");

    if (fp == NULL) {
        perror("Failed: ");
        exit(0);
    }

    printf("Input file: %s\n", filePath);

    char line[MAXSIZELINE];
    char *endPtr = NULL;
    int index = 0;
    int base = 10;
    unsigned long long int ull = 0;
    while (fgets(line, MAXSIZELINE, fp) != NULL) {
        // This is the worst thing I meet!
        // Fucking windows endlines! \r\n!
        // Thanks to https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
        strtok(line, "\r");

        // Convert input string numbers to unsigned long long integers
        ull = strtoull(line, &endPtr, base);
        assert(endPtr != NULL);
        // Store them into a buffer
        numbers[index] = ull;
        index++;
    }

    // Print to stdout the input file
    int i = 0;
    while (numbers[i]) {
        printf("%d:%llu\n", i + 1, numbers[i]);
        i++;
    }

    fclose(fp);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solveFile(argv[i]);
    }
    return 0;
}
