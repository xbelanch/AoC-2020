#include <stdio.h>
#include <stdlib.h>

int parse_file(char *filename) {
    fprintf(stdout, "Input file: %s\n", filename);

    return 0;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        parse_file(argv[i]);
    }

    return 0;
}
