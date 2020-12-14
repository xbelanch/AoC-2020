#include <stdlib.h>
#include <stdio.h>

void parseInput(char* filename)
{
    FILE *file;
    if ((file = fopen(filename, "r")) == NULL) {
        printf("ERROR:: opening file %s\n", filename);
        exit(-1);
    }

    // reads text until new line is encountered
    char c[1000];
    fscanf(file, "%[^\n]", c);

    printf("Data from the file:\n%s\n", c);

    fclose(file);

}

int main(int argc, char *argv[])
{
    parseInput(argv[1]);
    return 0;
}
