#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXSIZELINE 512
#define MAXSIZELINES 2048

unsigned long long int numbers[MAXSIZELINES];
unsigned long long int range[32];

void printValues() {
    int i = 0;
    while (numbers[i]) {
        printf("%d:%llu\n", i + 1, numbers[i]);
        i++;
    }
}

int findEncryptionWeakness(){
    unsigned long long lowest;
    unsigned long long largest;
    unsigned long long tmp;

    tmp = range[0];
    lowest = range[0];
    largest = range[0];
    for (int i = 1; range[i] != 0; i++) {
        tmp = range[i];
        if (tmp < lowest) {
            lowest = tmp;
        }
        if (tmp > largest) {
            largest = tmp;
        }
    }
    printf("lowest: %llu\n", lowest);
    printf("largest: %llu\n", largest);
    printf("Sum of smallest and largest: %llu\n", lowest + largest);
return 0;
}

int solvePartTwo(int start, int limit, unsigned long long int match) {
    unsigned long long int sum = 0;
    /* unsigned long long int smallest = numbers[start]; */
    for (int i = start; i < limit; i++) {
        sum += numbers[i];
        if (sum == match) {
            printf("Match: %llu \n", sum);
            for (int j = start; j < i ; j++) {
                printf("%llu + ", numbers[j]);
                range[j - start] = numbers[j];
            }
            printf("%llu = %llu\n", numbers[i], match);
            range[i - start] = numbers[i];
            // TODO:
            // find the smallest and largest number
            // of a contiguous range.
findEncryptionWeakness();

            return -1;
        }
        if (sum > match) {
            return 0;
        }
    }

    return 1;
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
    return start;
}


int solveFile(char *filePath, int preamble) {
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

    int nonmatch = 0;
    for (int i = preamble; numbers[i]; i++) {
        nonmatch = solveSampleFile(i, preamble);
        if (nonmatch > 0) {
            return nonmatch;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int solution = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp("sample-01.txt", argv[i]) == 0) {
            solution = solveFile(argv[i], 5);
        } else {
            solution = solveFile(argv[i], 25);
        }

        if (solution > 0) {
            printf("Solution for Part One: %llu\n", numbers[solution]);
        }

        for (int i = 0; i < MAXSIZELINES; i++) {
            if (solvePartTwo(i, i + 512, numbers[solution]) < 0)
                break;
        }
    }
    return 0;
}
