#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_TURNS 2020

typedef struct {
    size_t turn;
    size_t value;
} Number;

Number numbers[MAX_TURNS];

void LOG(size_t max) {
    if (max > MAX_TURNS)
        return;
    for (size_t i = 0; i < max; ++i) {
        fprintf(stdout, "Turn %lu: %lu\n", numbers[i].turn, numbers[i].value);
    }
}

size_t find_last_two_occurrences(size_t number, size_t turn) {
    Number *occurrences = malloc(sizeof(Number) * 2);
    size_t found = 0;
    for (int i = turn; i >= 0; --i) {
        if (numbers[i].value == number) {
            occurrences[found].value = numbers[i].value;
            occurrences[found].turn = numbers[i].turn;
            found++;
        }

        if (found == 2) {
            size_t diff = occurrences[0].turn - occurrences[1].turn;
            free(occurrences);
            return diff;
        }
    }
    free(occurrences);
    return 0;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    // Initialize the puzzle
    char *input_sample_puzzle = "20,0,1,11,6,3";
    char *ptr = input_sample_puzzle;
    char *start = input_sample_puzzle;
    size_t count = 0;
    char *val = malloc(sizeof(char) * 32);
    val[0] = '\0';
    size_t len = 0;
    while (*ptr != '\0') {
        if (*ptr != ',') {
            len++;
        } else {
            strncpy(val, start, len);
            val[len] = '\0';
            start = ptr + 1;
            numbers[count].turn = count + 1;
            numbers[count].value = atoll(val);
            val[0] = '\0';
            len = 0;
            count++;
        }
        ptr++;
    }

    // add last data of the input puzzle
    strncpy(val, start, len);
    numbers[count].turn = count + 1;
    numbers[count].value = atoll(val);
    count++;
    free(val);

    fprintf(stdout, "Sample puzzle: %s\n", input_sample_puzzle);

    while (count < MAX_TURNS + 1) {
        size_t n = find_last_two_occurrences(numbers[count - 1].value, count - 1);
        numbers[count].value = n;
        numbers[count].turn = count + 1;
        count++;
    }
    // LOG(MAX_TURNS);

    fprintf(stdout, "Solution for part One: %lu\n", numbers[MAX_TURNS - 1].value);

    return 0;
}
