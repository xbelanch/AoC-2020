#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXARRAYSIZE 1024

// Recursion implementation (bad idea)
uint64_t fib_recursion_method(int n) {
    if (n <= 2) return 1;
    return fib_recursion_method(n - 1) + fib_recursion_method(n - 2);
}

// Memoization implementation
uint64_t fib_memoization_method(int n, uint64_t memo[]) {
    if (memo[n] > 0)
        return memo[n];

    if (n <= 2) return 1;

    memo[n] = fib_memoization_method(n - 1, memo) + fib_memoization_method(n - 2, memo);
    return memo[n];
}


int main(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++) {
        int number = atoi(argv[i]);
        uint64_t result;

        // resolve fib by recursion
        result = fib_recursion_method(number);
        printf("fib(%d)=%llu\n", number, result);

        // initialize array
        uint64_t memo[MAXARRAYSIZE];
        for (int i = 0; i < MAXARRAYSIZE; i++)
            memo[i] = 0;

        // resolve fib by memoization
        result = fib_memoization_method(number, memo);
        printf("fib(%d)=%llu\n", number, result);
    }
    return 0;
}
