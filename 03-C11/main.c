#include <stdlib.h>
#include <stdio.h>

#define PRINT(msg, pattern) printf(msg ": %s\n", pattern)
#define MAXBUFFER 1024

char* repeatPattern(char* pattern, int times)
{
    char* buffer = malloc(sizeof(char) * MAXBUFFER);

    // get the length of pattern string
    int len = 0;
    for (int i = 0; pattern[i] != '\0'; i++) len++;

    // prevent buffer overflow
    if ((len * times) >= MAXBUFFER) {
        printf("Result is more than buffer can handle\n");
        return -1;
    }

    // duplicate n times pattern
    int end = 0;
    for (int i = 0; i < 3; i++) {
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
    char map[256][256];

    if ((file = fopen(filename, "r")) == NULL) {
        printf("ERROR:: opening file %s\n", filename);
        exit(-1);
    }

    printf("File %s loaded\n", filename);

    int j = 0;
    char* row;
    while (fscanf(file, "%s[^\n]", row) != EOF ) {
        for (int z = 0; z < 2; z++) {
            for (int i = 0; row[i] != '\0'; i++) {
                map[j][i + (z * i)] = row[i];
            }
       }
        j++;
    }
    for (int i = 0; i < 10; i++) {
        printf("%s\n", map[i]);
    }

    // testing with the first line
    /* char* row = malloc(sizeof(char) * 128); */
    /* int posX = 3; */
    /* int posY = 0; */
    /* int trees = 0; */
    /* while (fscanf(file, "%s[^\n]", row) != EOF) { */
    /*     if (posY > 0) { */
    /*         if ( row[posX] != NULL ) { */

    /*             if (row[posX] == '#') { */
    /*                 row[posX] = 'X'; */
    /*                 trees++; */
    /*             } else { */
    /*                 row[posX] = 'O'; */
    /*             } */
    /*             posX += 3; */

    /*         } else { */
    /*             break; */
    /*         } */
    /*     } */
    /*     printf("%d%s\n", posY, row); */
    /*     posY++; */
    /* }; */

    /* printf("How many trees would you encounter? %d\n", trees); */


    /* // Check how many trees are in that row */
    /* int trees = 0; */
    /* for (int i = 0; row[i] != '\0'; i++) { */
    /*     if (row[i] == '#') trees++; */
    /* } */
    /* printf("Trees: %d\n", trees); */

    fclose(file);
}


int main(int argc, char *argv[])
{
    if (argc > 0) {
        char* pattern = "..##.......#";
        PRINT("Original pattern", pattern);
        char* result = repeatPattern(pattern, 4);
        PRINT("Result pattern", result);
        /* parseInput(argv[1]); */
    }

    return 0;
}
