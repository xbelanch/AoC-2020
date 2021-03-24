#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// A naive method to find modular
// multiplicative inverse of 'j'
// under modulo 'k'
int inverse_modulus(uint64_t j, uint64_t k) {
    if (j % k == 1) {
        return 1;
    } else {
        int factor = 2;
        for (;;) {
            int r = (j * factor) % k;
            if (r == 1) {
                return factor;
            } else {
                factor = factor + 1;
            }
        }
    }
}


// Solve this sample from AoC: 67,7,59,61 first occurs at timestamp 754018.
int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    printf("Chinese Reminder Theorem\n");
    // It works given 7,13,x,x,59,x,31,19 -> 1068781
    /* int v[] = {7, 13, 59, 31, 19}; */
    /* int v[] = {67, 7, 59, 61}; */
    int v[] = {1789, 37, 47, 1889};

    uint64_t product = 1;

    for (int i = 0; i < (int)(sizeof(v) / sizeof(v[0])); i++) {
        product *= v[i];
    }

    int b[] = {
                    0,
                    v[1] - 1,
                    v[2] - 2,
                    v[3] - 3
    };

    uint64_t p;
    uint64_t sum = 0;
	for (int i = 0; i < (int)(sizeof(v) / sizeof(v[0])); i++) {
		p = product / v[i];
		sum += b[i] * inverse_modulus(p, v[i]) * p;
	}
    printf("Wow: %lu\n", sum % product);

   return 0;
}
