#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_TURNS 2020
// #define MAX_TURNS 30000000

typedef struct {
    size_t turn;
    size_t value;
} Number;

typedef struct {
    size_t value;
    size_t turns[1024];
    size_t len;
} Turns;

typedef struct {
    Turns number[1024];
    size_t len;
} NumberPart2;

Number numbers[MAX_TURNS];
NumberPart2 nums;

void LOG(size_t max) {
    if (max > MAX_TURNS)
        return;
    for (size_t i = 0; i < max; ++i) {
        fprintf(stdout, "Turn %lu: %lu\n", numbers[i].turn, numbers[i].value);
    }
}

void LOG_PART_TWO() {
    for (size_t i = 0; i < nums.len; ++i) {
        fprintf(stdout, "%lu: ", nums.number[i].value);
        for (size_t j = 0; j < nums.number[i].len; ++j) {
            fprintf(stdout, "%lu, ", nums.number[i].turns[j]);
        }
        printf("\n");
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
    // char *input_sample_puzzle = "20,0,1,11,6,3";
    char *input_sample_puzzle = "0,3,6";
    char *ptr = input_sample_puzzle;
    char *start = input_sample_puzzle;
    size_t turns = 0;
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
            numbers[turns].turn = turns + 1;
            numbers[turns].value = atoll(val);
            // Second day
            nums.number[turns].value = atoll(val);
            nums.number[turns].turns[0] = turns + 1;
            nums.number[turns].len++;
            nums.len++;

            val[0] = '\0';
            len = 0;
            turns++;
        }
        ptr++;
    }

    // add last data of the input puzzle
    strncpy(val, start, len);
    numbers[turns].turn = turns + 1;
    numbers[turns].value = atoll(val);

    // Add last number turn Second day
    nums.number[turns].value = atoll(val);
    nums.number[turns].turns[0] = turns + 1;
    nums.number[turns].len++;
    nums.len++;

    turns++;
    free(val);

    fprintf(stdout, "Sample puzzle: %s\n", input_sample_puzzle);

    size_t cursor = turns - 1;
    int found = 0;
    int zero = -1;
    size_t solution = 0;
    while (turns < 6121) {
        // first time we found that number
        // fprintf(stdout, "Cursor: %lu | with len: %lu | turns: %lu\n",
        //         cursor,
        //         nums.number[cursor].len,
        //         turns);
        if (nums.number[cursor].len == 1) {
            // next number is zero
            // add it to its array of turns
            for (size_t i = 0; i < nums.len; ++i) {
                if (nums.number[i].value == 0) {
                    zero = i;
                    size_t len = nums.number[i].len;
                    nums.number[i].turns[len++] = turns + 1;
                    nums.number[i].len++;
                    cursor = i;
                }
            }

            if (zero < 0) {
                printf("Create zero\n");
                nums.number[nums.len].value = 0;
                nums.number[nums.len].turns[0] = turns + 1;
                nums.number[nums.len].len++;
                cursor = nums.len;
                zero = nums.len;
                nums.len++;
            }
        } else {
            size_t len = nums.number[cursor].len;
            size_t delta = nums.number[cursor].turns[len - 1] - nums.number[cursor].turns[len - 2];
            // printf("delta: %lu turns: %lu cursor: %lu\n", delta, turns, cursor);
            for (size_t i = 0; i < nums.len; ++i) {
                // new number!
                if (nums.number[i].value == delta) {
                    size_t _len = nums.number[i].len;
                    nums.number[i].turns[_len++] = turns + 1;
                    nums.number[i].len++;
                    cursor = i;
                    found = 1;
                    if (turns + 1 == MAX_TURNS) {
                        solution = nums.number[i].value;
                    }
                    break;
                }
            }
            if (!found) {
                // printf("Found new number (%lu)!\n", delta);
                nums.number[nums.len].value = delta;
                nums.number[nums.len].turns[0] = turns + 1;
                if (turns + 1 == MAX_TURNS) {
                    solution = delta;
                }
                nums.number[nums.len].len++;
                nums.len++;
                cursor = nums.len - 1;
            }
        }
        found = 0;
        turns++;
    }
    LOG_PART_TWO();

    fprintf(stdout, "Solution for part One: %lu\n", solution /* nums.number[nums.len-1].value */ );

    return 0;
}
