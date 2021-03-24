#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int inverse_modulus(int j, int k) {
    if (j % k == 1) {
        return 1;
    } else {
        int factor = 2;
        while (1) {
            int r = (j * factor) % k;
            if (r == 1) {
                return factor;
            } else {
                factor = factor + 1;
            }
        }
    }
}


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    printf("Chinese Reminder Theorem\n");
    int v[] = {5, 7, 8};
    int NN = v[0] * v[1] * v[2];
    int b[] = {3, 1, 6};
    int N[] = {
               v[1] * v[2],
               v[0] * v[2],
               v[0] * v[1]
    };

    for (int i = 0; i < (int)(sizeof(N)/sizeof(N[0])) ; i++) {
        printf("N%d: %d\n", i, N[i]);
    };

    int x[3];
    for (int i = 0; i < (int)(sizeof(N)/sizeof(N[0])); i++) {
        x[i] = inverse_modulus(N[i], v[i]);
    }

    for (int i = 0; i < (int)(sizeof(x)/sizeof(x[0])); i++) {
        printf("x%d: %d\n", i, x[i]);
    };

    uint64_t bnx[3];
    uint64_t r = 0;
    for (int i = 0; i < 3; i++) {
        bnx[i] = b[i] * N[i] * x[i];
        r += bnx[i];
        printf("bnx[%d] = %lu\n", i, bnx[i]);
    }

    printf("r: %lu\n", r);
    printf("Result? %lu", r % NN);
    return 0;
}
