#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int adapters[1024];
int diff_one_jolt = 0;
int diff_three_jolt = 0;

// Sort the array in ascending order
// https://www.programmingsimplified.com/c/source-code/c-program-bubble-sort
// -------------------------------------------------------------------------
void bubbleSort() {
    int length = 0;
    while (adapters[length]) {
        length++;
    }

    int c, d, t;
    for (c = 0 ; c < length - 1; c++) {
        for (d = 0 ; d < length - c - 1; d++) {
            if (adapters[d] > adapters[d+1]) {
                /* Swapping */
                t         = adapters[d];
                adapters[d]   = adapters[d+1];
                adapters[d+1] = t;
            }
        }
    }
}

// Find the length of array of integers
// ------------------------------------
int lengthArray(int *array) {
    int *i;
    int n = 0;
    for (i = array; *i; i++) {
        n++;
    }
    return n;
}


// Solution for part One of Day 10
// -------------------------------
int partOne() {
    bubbleSort();
    int start = 0;
    for (int i = 0; adapters[i]; i++) {
        if (adapters[i] - start == 1) {
            diff_one_jolt++;
        } else if (adapters[i] - start == 3) {
            diff_three_jolt++;
        }
        start = adapters[i];
    }

    printf("There are %d differences of 1 jolt and %d differences of 3 jolts\n", diff_one_jolt, diff_three_jolt + 1);
    int solution = diff_one_jolt * (diff_three_jolt + 1);

    diff_one_jolt = 0; // reset diff values
    diff_three_jolt = 0;

    return solution;
}

uint64_t variations = 0;

void solveArrangements(int index, int len) {

    /* printf("%d, ", adapters[index]); */

    if (adapters[index] == adapters[len - 1]) {
        /* printf("\n"); */
        variations++;
        return;
    }

    if (adapters[index + 1] - adapters[index] == 1 || adapters[index + 1] - adapters[index] == 3) {
        solveArrangements(index + 1, len);
    }

    if (adapters[index + 2] - adapters[index] == 2) {
        solveArrangements(index + 2, len);
    }

    if (adapters[index + 3] - adapters[index] == 3) {
        solveArrangements(index + 3, len);
    }

}

// Solution for part Two of Day 10
// -------------------------------
uint64_t partTwo() {

    // Sort array
    bubbleSort();

    // Add last number to array
    int len = lengthArray(adapters);
    adapters[len] = adapters[len - 1] + 3;

    // Add 0 value at beginning of array
    len = lengthArray(adapters);
    for (int i = len; i >= 0; i--) {
        adapters[i + 1] = adapters[i];
    }

    len = lengthArray(adapters);
    adapters[0] = 0;

    solveArrangements(0, len);

    return variations;
}


void parse_file(FILE *fp) {
    char lines[8];
    int index = 0;
    while (fgets(lines, 8, fp) != NULL) {
        strtok(lines, "\r"); // Remove fucking windows return carriage
        adapters[index] = atoi(lines); // Store them into a buffer
        index++;
    }
}

void print_joltage_ratings() {
    int index = 0;
    while (adapters[index]) {
        printf("%d:%d\n", index, adapters[index]);
        index++;
    }
}

int solve_file(char *filepath) {
    printf("Filepath: %s\n", filepath);
    FILE *fp;
    fp = fopen(filepath, "rb");
    if (fp == NULL) {
        perror("FAIL");
    }

    // parse and store the content of the file
    // ---------------------------------------
    parse_file(fp);

    // print file content for testing purpose
    // ---------------------------------------
    /* print_joltage_ratings(); */

    // find solution for part One
    // --------------------------
    /* printf("Solution for part one: %d\n", partOne()); */

    // find solution for part Two
    // --------------------------
    printf("Solution for part two: %lld\n", partTwo());

    fclose(fp);
    return 0;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
