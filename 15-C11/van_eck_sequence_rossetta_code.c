#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    const size_t max = 30000000;
    const size_t limit = 11;
    size_t *a = malloc(max * sizeof(size_t));
    size_t *b = malloc(max * sizeof(size_t));
    // size_t input[] = {20,0,1,11,6,3};
    size_t input[] = {0,3,6};
    size_t len = (sizeof(input) / sizeof(input[0]));
    for (size_t i = 0; i < len; ++i)
        a[i] = input[i];

    for (size_t n = 0; n < max - 1; n ++) {
        // printf("a[%lu] = %lu | b[%lu] = %lu\n", n, a[n], a[n], b[a[n]]);
        // if (1000000 % n == 0)
        //     fprintf(stdout, "1000000\n");

        if (b[a[n]] != 0) {
            // printf("b[%lu] = %lu\n", a[n], b[a[n]]);
            a[n + 1] = n - b[a[n]];
            b[a[n]] = n;
        } else {
            for (int m = n - 1; m >= 0; m --) {
                if (a[m] == a[n]) {
                    a[n+1] = n - m;
                    b[a[n]] = n;
                    // printf("\tb[%lu] = %lu\n", a[n], b[a[n]]);
                    break;
                }
            }
        }
    }

    putchar('\n');
    for (size_t i = 0; i < limit; i++) printf("%lu ", a[i]);
    putchar('\n');
    for (size_t i = 0; i < limit; i++) printf("- ");
    putchar('\n');
    for (size_t i = 0; i < limit; i++) printf("%lu ", b[i]);
    putchar('\n');
    for (size_t i = 0; i < limit; i++) printf("- ");
    putchar('\n');
    for (size_t i = 0; i < limit; i++) printf("%lu ", i);
    putchar('\n');
    fprintf(stdout, "Solution: %lu\n", a[max - 1]);
    free(a);
    free(b);
}
