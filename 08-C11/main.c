#include <stdio.h>
#include <stdlib.h>


void solveInput(char *filepath) {
    printf("Input file: %s\n", filepath);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solveInput(argv[i]);
    }
    return 0;
}
