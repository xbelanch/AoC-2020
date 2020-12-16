#include <stdlib.h>
#include <stdio.h>

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


unsigned long parseInput(char* filename)
{
    FILE* file;
    char* map[1024];

    if ((file = fopen(filename, "r")) == NULL) {
        printf("ERROR:: opening file %s\n", filename);
        exit(-1);
    }

    printf("File %s loaded\n", filename);

    // Store the input data
    int row = 0;
    int pattern_repeat = 256; // why I choose this number?
    char* pattern = malloc(sizeof(char) * 512);
    while (fscanf(file, "%s", pattern) != EOF ) {
        map[row++] = repeatPattern(pattern, pattern_repeat);
    }

    // traverse the map and change the trees or open squares
    // by X or O characters
    int tree = 0;
    int column = 0;
    int right[5] ={1, 3, 5, 7, 1};
    int down[5] ={1, 1, 1, 1, 2};
    int solution[5];

    for (int k = 0; k < 5; k++) {
        printf("Test for right: %d, down: %d\n", right[k], down[k]);
        for (int i = 0; i < row; i = i + down[k]) {
            /* printf("%s\n", map[i + down[k]]); */
            if (map[i][column] == '#') {
                tree++;
            };
            column += right[k];
        }

        // store how many trees encountered in that slope
        solution[k] = tree;
        printf("Trees encountered at slope %d: %d\n", k + 1, solution[k]);

        // reset some variables
        tree = 0;
        column = 0;
    }

    fclose(file);

    // Part two solution
    // FUCKING 64 bits!!!!!!
    unsigned long partTwo = 1;
    for (int i = 0; i < 5; i++) {
        partTwo *= solution[i];
    }
    return partTwo;
}

int main(int argc, char *argv[])
{
    if (argc > 0) {
        for (int i = 1; i < argc; i++) {
            unsigned long solutionPartTwo = parseInput(argv[i]);
            printf("Answer part two: %ld\n", solutionPartTwo);
        }
    }

    return 0;
}
