#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int adapters[1024];

void parse_file(FILE *fp) {
    char lines[8];
    int index = 0;
    while (fgets(lines, 8, fp) != NULL) {
        strtok(lines, "\r"); // Remove fucking windows return carriage
        adapters[index] = atoi(lines); // Store them into a buffer
        index++;
    }
}

void print_joltage_ratings() {
    int index = 0;
    while (adapters[index]) {
        printf("%d:%d\n", index, adapters[index]);
        index++;
    }
}

int solve_file(char *filepath) {
    printf("Filepath: %s\n", filepath);
    FILE *fp;
    fp = fopen(filepath, "rb");
    if (fp == NULL) {
        perror("FAIL");
    }

    // parse and store the content of the file
    // ---------------------------------------
    parse_file(fp);

    // print file content for testing purpose
    // ---------------------------------------
    print_joltage_ratings();

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
