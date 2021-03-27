#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int busID;
    int offset;
} Bus;

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


// A naive method to find modular
// multiplicative inverse of 'j'
// under modulo 'k'
int inverse_modulus(uint64_t j, uint64_t k) {
    if (j % k == 1) {
        return 1;
    } else {
        int factor = 2;
        for (;;) {
            int r = (j * factor) % k;
            if (r == 1) {
                return factor;
            } else {
                factor = factor + 1;
            }
        }
    }
}

uint64_t solutionPartTwo(Bus buses[], int size) {

    uint64_t solution = 0;
    for (int i = 0; i < size; i++) {
        printf("bus id: %d, offset: %d\n", buses[i].busID, buses[i].offset);
    }

    uint64_t product = 1;
    int b[size];
    for (int i = 0; i < size; i++) {
        product *= buses[i].busID;
        b[i] = buses[i].busID - buses[i].offset;
    }

    uint64_t p;
    uint64_t sum = 0;
	for (int i = 0; i < size; i++) {
		p = product / buses[i].busID;
		sum += b[i] * inverse_modulus(p, buses[i].busID) * p;
	}

    return sum % product;
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
    int number_line = 0, timestamp = 0;
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
    // Working on part two solution
    Bus buses[128];
    int offset = 0;
    while (ptr != NULL) {
        if (*ptr != 'x') {
            busIDs[manyBusIDs] = atoi(ptr);
            buses[manyBusIDs].busID = busIDs[manyBusIDs];
            buses[manyBusIDs].offset = offset;
            manyBusIDs += 1;
            offset += 1;
        } else {
            offset += 1;
        }
        ptr = strtok(NULL, ",");
    }

    // Get solution for part One
    int partOneSolution =  solutionPartOne(timestamp, busIDs, manyBusIDs);
    printf("Solution for part one: %d\n", partOneSolution);

    // Get solution for part Two
    uint64_t partTwoSolution = solutionPartTwo(buses, manyBusIDs);
    printf("Solution for part two: %ld\n", partTwoSolution);

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
