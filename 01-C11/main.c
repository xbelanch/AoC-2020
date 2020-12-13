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

int main(int argc, char *argv[])
{
    int *numbers;

    for (int i = 1; i < argc; i++) {
        numbers = parseInput(argv[i]);
    };

    printf("I get %d if I multiply them together\n", getResult(numbers));

    return 0;
}
