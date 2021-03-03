#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int solve_file(char *filename) {
    printf("Input file: %s\n", filename);
    return 0;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
