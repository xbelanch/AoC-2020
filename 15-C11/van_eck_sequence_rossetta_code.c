#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    const size_t max = 30 * 1000 * 1000;
    const size_t limit = 10;
    size_t *a = malloc(max * sizeof(size_t));
    size_t *hashmap = malloc((max + 100) * sizeof(size_t));

    for (size_t i = 0; i < max; ++i) {
        a[i] = -1;
    }
    // initialize hashmap
    for (size_t i = 0; i < (max + 100); ++i) {
        hashmap[i] = -1;
    }

    size_t input[] = {20,0,1,11,6,3};
    //size_t input[] = {0,3,6};
    size_t len = (sizeof(input) / sizeof(input[0]));

    for (size_t i = 0; i < len; ++i) {
        a[i] = input[i];
        hashmap[a[i]] = i;
    }

    for (size_t n = len - 1; n < max - 1; n++) {
        if (hashmap[a[n]] != -1) {
            a[n + 1] = n - hashmap[a[n]];
            hashmap[a[n]] = n;
        } else {
            // Optimized with a "hashmap" xD
            a[n + 1] = 0;
            hashmap[a[n]] = n;
            // for (int m = n - 1; m >= 0; m --) {
            //     if (a[m] == a[n]) {
            //         a[n+1] = n - m;
            //         hashmap[a[n]] = n;
            //         // printf("\tb[%lu] = %lu\n", a[n], b[a[n]]);
            //         break;
            //     }
            // }
        }
    }

    putchar('\n');
    for (size_t i = 0; i < limit; i++) printf("%lu ", a[i]);
    putchar('\n');
    for (size_t i = 0; i < limit; i++) printf("- ");
    putchar('\n');
    for (size_t i = 0; i < limit; i++) printf("%lu ", hashmap[i]);
    putchar('\n');
    for (size_t i = 0; i < limit; i++) printf("- ");
    putchar('\n');
    for (size_t i = 0; i < limit; i++) printf("%lu ", i);
    putchar('\n');
    fprintf(stdout, "Solution for Day 15: %lu\n", a[max - 1]);
    free(a);
    free(hashmap);
}
