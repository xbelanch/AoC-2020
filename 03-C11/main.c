#include <stdlib.h>
#include <stdio.h>

void parseInput(char* filename)
{
    FILE* file;

    if ((file = fopen(filename, "r")) == NULL) {
        printf("ERROR:: opening file %s\n", filename);
        exit(-1);
    }

    printf("File %s loaded\n", filename);

    fclose(file);
}


int main(int argc, char *argv[])
{
    if (argc > 0) {
        parseInput(argv[1]);
    }

    return 0;
}
