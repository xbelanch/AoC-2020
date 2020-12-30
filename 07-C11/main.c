#include <stdio.h>
#include <stdlib.h>

void solve_file(char* filename) {
    printf("Filename: %s", filename);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
