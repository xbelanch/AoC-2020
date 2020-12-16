#include <stdlib.h>
#include <stdio.h>

#define PRINT(msg, pattern) printf(msg ": %s\n", pattern)

// Globals
int buffersize = 0;

char* repeatPattern(char* pattern, int times)
{
    // get the length of pattern string
    int len = 0;
    for (int i = 0; pattern[i] != '\0'; i++) len++;

    buffersize = len * times;

    // prevent buffer overflow
    char* buffer = malloc(sizeof(char) * buffersize);

    // avoid stupidity
    if (times == 0) times = 1;

    // duplicate n times pattern
    int end = 0;
    for (int i = 0; i < times; i++) {
        for (int j = 0; j < len; j++) {
            buffer[(len * i) + j] = pattern[j];
            end++;
        }
    }

    // set end of string
    buffer[end] = '\0';

    return buffer;
}


void parseInput(char* filename)
{
    FILE* file;
    char* map[1024];

    if ((file = fopen(filename, "r")) == NULL) {
        printf("ERROR:: opening file %s\n", filename);
        exit(-1);
    }

    printf("File %s loaded\n", filename);

    int row = 0;
    char* pattern = malloc(sizeof(char) * 128);
    // Store the input data
    while (fscanf(file, "%s", pattern) != EOF ) {
        // 323 : total of lines of input text
        // we need to solve this before
        map[row++] = repeatPattern(pattern, 323);
    }

    printf("Total of lines: %d\n", row);

    // traverse the map and change the trees or open squares
    // by X or O characters
    int tree = 0;
    int column = 3;
    for (int i = 1; i < row; i++) {
        if (map[i][column] == '#') {
            // found a tree!
            // map[i][column] = 'X';
            tree++;
        };

        /* if (map[i][column] == '.') { */
        /*     map[i][column] = 'O'; */
        /* } */
        column += 3;
    }

    printf("How many trees would you encounter? %d\n", tree);


    fclose(file);
}


int main(int argc, char *argv[])
{
    if (argc > 0) {
        parseInput(argv[1]);
    }

    return 0;
}
