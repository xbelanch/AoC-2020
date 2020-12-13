#include <stdio.h>
#include <stdlib.h>

int numbers[999];

int parseInput(char *filename)
{
    int i = 0;
    int number;
    /* int* tmp; */

    // Open, Read and close the input file
    FILE *file;

    file = fopen(filename, "r");

    if (file == NULL) {
        exit(-1);
    }

    while ( fscanf(file, "%d", &number)!= EOF) {
        numbers[i++] = number;
    }

    // we remove all the null entries of the array
    /* tmp = realloc(numbers, i*sizeof(int)); */
    /* free(numbers); */
    /* numbers = tmp; */

    fclose(file);

    return i;
}

// Brute force!
void calculateNumber(int length)
{
    printf("We have at the moment %d numbers\n", length);
    for (int i = 0; i < length; i++) {
        int entry = numbers[i];
        for (int j = 0; j < length ; j++) {
            if ((entry + numbers[j]) == 2020 && (entry != numbers[j])) {
                printf("The two entries that sum to 2020 are %d and %d\n", entry, numbers[j]);
                printf("I get %d if I multiply them together\n", entry * numbers[j]);
                break;
            }
        }
    }
}


int main(int argc, char *argv[])
{
    int length;

    for (int i = 1; i < argc; i++) {
        length = parseInput(argv[i]);
    };

    calculateNumber(length);


    return 0;
}
