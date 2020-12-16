#include <stdio.h>
#include <stdlib.h>

int *parseInput(char *filename)
{
    int* numbers;
    int* tmp;
    int i = 0;
    int number;

    // allocate memory for array of numbers
    numbers = (int*)malloc(sizeof(int) * 999);

    // open, Read and close the input file
    FILE *file;

    file = fopen(filename, "r");

    if (file == NULL) {
        exit(-1);
    }

    // parse the numbers of the input text file
    while ( fscanf(file, "%d", &number)!= EOF) {
        numbers[i++] = number;
    }

    // reallocate the memory of the array of numbers
    tmp = (int*)malloc(sizeof(int) * i);
    for (int j = 0; j < i; j++) {
        tmp[j] = numbers[j];
    }

    free(numbers);
    numbers = tmp;

    fclose(file);

    return numbers;
}

// Brute force
int getResult(int *numbers)
{
    int len = 0;

    for (int i = 0; numbers[i] != '\0'; i++) len++;

    printf("We have %d numbers\n", len);

    for (int i = 0; i < len; i++) {
        int entry1 = numbers[i];
        for (int j = 0; j < len; j++) {
            if (i != j) { // don't sum same entries of the list
                int entry2 = numbers[j];
                if (entry1 + entry2 == 2020) {
                    printf("The two entries that sum to 2020 are %d and %d\n", entry1, entry2);
                    return entry1 * entry2;
                }
            }
        }
    }

    return -1; // no result
}
// Is really different from the brute force function?
int getResultPartOne(int *numbers)
{
    int len = 0;
    for (int i = 0; numbers[i] != '\0'; i++) len++;

    for (int i = 1; i < len; i++) {
        for (int j = len - 2; j >= 0 ; j--) {
            if (numbers[i] + numbers[j] == 2020) {
                printf("The two entries that sum to 2020 are %d and %d\n", numbers[i], numbers[j]);
                return numbers[i] * numbers[j];
            }
        }
    }

    return -1;
}


/* int getResult3(int *numbers) */
/* { */
/*     int len = 0; */
/*     for (int i = 0; numbers[i] != '\0'; i++) len++; */

/*     // need to sort the numbers from low value to high value */

/*     for (int i = 1; i < len; i++) { */
/*         for (int j = len - 2; j >= 0 ; j--) { */
/*             if (numbers[j] == 2020 - numbers[i]) { */
/*                 printf("The two entries that sum to 2020 are %d and %d\n", numbers[i], numbers[j]); */
/*                 return numbers[i] * numbers[j]; */
/*             } */
/*         } */
/*     } */

/*     return -1; */
/* } */


// Part two
int getResultPartTwo(int *numbers)
{
    int len = 0;
    for (int i = 0; numbers[i] != '\0'; i++) len++;

    for (int i = 1; i < len; i++) {
        for (int j = len - 2; j >= 0 ; j--) {
            for (int k = 1; k < len; k++) {
                if (numbers[i] + numbers[j] + numbers[k] == 2020) {
                    printf("The three entries that sum to 2020 are %d, %d and %d\n", numbers[i], numbers[j], numbers[k]);
                    return numbers[i] * numbers[j] * numbers[k];
                }
            }
        }
    }

    return -1;
}



int main(int argc, char *argv[])
{
    int *numbers;

    for (int i = 1; i < argc; i++) {
        numbers = parseInput(argv[i]);
    };

    /* printf("I get %d if I multiply them together\n", getResult(numbers)); */
    printf("I get %d if I multiply them together\n", getResultPartOne(numbers));
    printf("I get %d if I multiply them together\n", getResultPartTwo(numbers));
    //    printf("I get %d if I multiply them together\n", getResult3(numbers));

    return 0;
}
