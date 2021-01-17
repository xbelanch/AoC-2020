#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXSIZELINE 512
#define MAXSIZELINES 2048

unsigned long long int numbers[MAXSIZELINES];

void printValues() {
    int i = 0;
    while (numbers[i]) {
        printf("%d:%llu\n", i + 1, numbers[i]);
        i++;
    }
}

int solveSampleFile(int start, int preamble) {
    for (int j = start - preamble; j < start; j++) {
        for (int k = start - preamble; k < start; k++) {
            if (j != k) {
                unsigned long long int sum = numbers[j] + numbers[k];
                if (sum == numbers[start]) {
                    return 0;
                }
            }
        }
    }
    printf("Non match for %llu\n", numbers[start]);
    return 1;
}


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

    fclose(fp);

    int preamble = 25;
    for (int i = preamble; numbers[i]; i++) {
        if (solveSampleFile(i, preamble))
           break;
    }
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solveFile(argv[i]);
    }
    return 0;
}
