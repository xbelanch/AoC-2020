#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINEBUFFER 2048
#define log(string) printf("> %s", string)

typedef struct passport {
    int byr;
    int iyr;
    int eyr;
    int hgt;
    char* hcl;
    char* ecl;
    unsigned long pid;
    int cid;
} Passport;

Passport* newPassword() {
    Passport* passport = malloc(sizeof(Passport));

    passport->byr = -1;
    passport->iyr = -1;
    passport->eyr = -1;
    passport->hgt = -1;
    passport->hcl = NULL;
    passport->ecl = NULL;
    passport->pid = 0;
    passport->cid = -1;

    return passport;
}

void parseInput(char* filename) {
    printf("%s:\n", filename);

    FILE* file = fopen(filename, "r");
    char* line = malloc(sizeof(char) * MAXLINEBUFFER);

    int passports = 0;
    while ( fgets(line, MAXLINEBUFFER, file) != NULL) {
        // Check for dos and unix EOL format
        // I'm not sure if this works under linux
        if (line[0] != '\r' && line[0] != '\n') {
            // log(line);
        } else {
            passports++;
        }
    }
    passports++; // count EOL as the last password of the input file
    printf("Number of passports: %d\n", passports);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        parseInput(argv[i]);
    }
    return 0;
}
