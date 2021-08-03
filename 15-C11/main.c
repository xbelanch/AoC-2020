#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    int *sample = malloc(sizeof(int) * 32);

    char *input_sample_puzzle = "0,3,6";
    char *ptr = input_sample_puzzle;
    size_t size = 0;
    while (*ptr != '\0') {
        if (*ptr != ',')
            sample[size++] = atoi(ptr);
        ptr++;
    }

    for (size_t i = 0; i < size; ++i) {
        fprintf(stdout, "data[%lu]: %d\n", i, sample[i]);
    }

    fprintf(stdout, "Sample puzzle: %s\n", input_sample_puzzle);
    return 0;
}
