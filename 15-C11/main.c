#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

typedef struct _startingnumbers {
    size_t *numbers;
    size_t len;
} StartingNumbers;

size_t starting_numbers[8][16] = {
    {0,3,6, -1},
    {1,3,2, -1},
    {2,1,3, -1},
    {1,2,3, -1},
    {2,3,1, -1},
    {3,2,1, -1},
    {3,1,2, -1},
    {20,0,1,11,6,3, -1},
};

StartingNumbers *startingNumbers[8];
size_t lenStartingNumbers = 0;

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    const size_t max = 30 * 1000 * 1000;
    // const size_t limit = 10;
    size_t *a = malloc(max * sizeof(size_t));
    size_t *hashmap = malloc((max + 100) * sizeof(size_t));

    for (size_t i = 0; i < 8; ++i) {
        if ((size_t)-1 != starting_numbers[i][0]) {
            startingNumbers[i] = malloc(sizeof(StartingNumbers));
            startingNumbers[i]->numbers = malloc(32 * sizeof(size_t));
            lenStartingNumbers++;

            size_t j = 0;
            while ((size_t)(-1) != starting_numbers[i][j]) {
                startingNumbers[i]->numbers[j] =starting_numbers[i][j];
                j++;
            }
            startingNumbers[i]->len = j;
        }
    }

    for (size_t i = 0; i < lenStartingNumbers; ++i) {

        for (size_t k = 0; k < max; ++k) {
            a[k] = -1;
        }
        // initialize hashmap
        for (size_t k = 0; k < (max + 100); ++k) {
            hashmap[k] = -1;
        }

        for (size_t j = 0; j < startingNumbers[i]->len; ++j) {
            a[j] = startingNumbers[i]->numbers[j];
            hashmap[a[j]] = j;
        }

        for (size_t n = startingNumbers[i]->len - 1; n < max - 1; n++) {
            if (hashmap[a[n]] != (size_t)-1) {
                a[n + 1] = n - hashmap[a[n]];
                hashmap[a[n]] = n;
            } else {
                a[n + 1] = 0;
                hashmap[a[n]] = n;
            }
        }

        fprintf(stdout, "Solution for Day 15: %lu\n", a[max - 1]);

    }
    free(a);
    free(hashmap);
}
