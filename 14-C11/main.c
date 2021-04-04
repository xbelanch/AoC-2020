#include <stdlib.h>
#include <stdio.h>

int solve_file(char *filepath) {
    printf("%s\n", filepath);
    return 0;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
