#include <stdio.h>
#include <stdlib.h>

void parseInput(char *filename)
{
    int i = 0;
    int numbers[999];
    int number;

    // Open, Read and close the input file
    FILE *file;

    file = fopen(filename, "r");

    if (file == NULL) {
        exit(-1);
    }

    while ( fscanf(file, "%d", &number)!= EOF) {
        numbers[i++] = number;
    }

    printf("We have at the moment %d numbers on %s", i, filename);

    fclose(file);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        parseInput(argv[i]);
    };

    return 0;
}
