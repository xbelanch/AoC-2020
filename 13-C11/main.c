#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Get solution for part One
int solutionPartOne(int timestamp, int busIDs[], int manyBusIDs) {
    int solution = 0;
    int minTime = timestamp - 10;
    int maxTime = timestamp + 10;
    int found = 0;
    while (!found && (minTime < maxTime)) {
        for (int i = 0; i < manyBusIDs; i++) {
            if (minTime % busIDs[i] == 0 && timestamp < minTime ) {
                found = 1;
                solution = (minTime - timestamp) * busIDs[i];
            }
        }
        minTime += 1;
    }
    return solution;
}

int solve_file(char *filename) {
    printf("Input file: %s\n", filename);
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        perror("File opening failed\n");
        return EXIT_FAILURE;
    }


    // read input file content
    const size_t line_size = 300;
    char *line = (char*)malloc(sizeof(char) * line_size);
    int number_line = 0;
    int timestamp = 0;
    char *rawBusIDs = (char*)malloc(sizeof(char) * line_size);

    while (fgets(line, 300, fp) != NULL) {
        if (number_line == 0)
            timestamp = atoi(line);
        if (number_line == 1)
            strcpy(rawBusIDs, line);
        number_line += 1;
    }

    /* printf("%d: %s", timestamp, rawBusIDs); */

    // Now we need to parse the rawBusIDs lines
    // and store them in a simple array
    int busIDs[128];
    int manyBusIDs = 0;
    char *ptr;
    ptr = strtok(rawBusIDs, ",");
    while (ptr != NULL) {
        if (*ptr != 'x') {
            busIDs[manyBusIDs] = atoi(ptr);
            manyBusIDs += 1;
        }
        ptr = strtok(NULL, ",");
    }


    // Get solution for part One
    int partOneSolution =  solutionPartOne(timestamp, busIDs, manyBusIDs);
    printf("Solution for part one: %d\n", partOneSolution);


    free(line);
    fclose(fp);
    return 0;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
