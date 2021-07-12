// Find out this topic on Stack Overflow
// warning: left shift count >= width of type

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    size_t pow_test = pow(2, 35);
    size_t pow_shift = 1UL << 35;

    fprintf(stdout, "pow: %lu, shift: %lu\n", pow_test, pow_shift);

    return 0;
}
