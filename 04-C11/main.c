#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXBUFFER 2048

// https://stackoverflow.com/questions/35178520/how-to-read-parse-input-in-c-the-faq
int parseInputDayOne(char* filename) {

    FILE* fp = fopen(filename, "rb");

    if (!fp)
        fprintf(stderr, "Cannot open %s: %s\n", filename, strerror(errno));

    char* buffer = malloc(sizeof(char) * MAXBUFFER);
    int newline = 1;
    char space = ' ';
    int match = 0;
    int valid = 0;

    while ( fgets(buffer, MAXBUFFER, fp) != NULL) {

        if (buffer[0] != '\r' && buffer[1] != '\n' ) {
            // Truncate lines
            for (char *p = strtok(buffer, "\r"); p; p = strtok(NULL, "\r")) {
                strncat(p, &space, 1);
                for (char *q = strtok(p, "\r"); q; q = strtok(NULL, "\r")) {
                    for (char *r = strtok(q, " "); r; r = strtok(NULL, " ")) {
                        /* printf("%s\n", r); */
                        if (strncmp("byr", r, 3) == 0 ||
                            strncmp("iyr", r, 3) == 0 ||
                            strncmp("eyr", r, 3) == 0 ||
                            strncmp("hgt", r, 3) == 0 ||
                            strncmp("hcl", r, 3) == 0 ||
                            strncmp("ecl", r, 3) == 0 ||
                            strncmp("pid", r, 3) == 0) match++;
                        // CID field is optional, so we dont count whatever if
                        // present or not
                        // if (strncmp("cid", r, 3) == 0
                    }
                }
            }
        } else {
            /* printf("Match: %d\n", match); */
            if (match == 7) valid++;
            match = 0;
            newline++;
            /* printf("\nPassport %d: \n", newline + 1); */
            continue;
        }
    }
    // last passport of the input
    /* printf("Match fields: %d\n", match); */
    if (match == 7) valid++;

    fclose(fp);

    printf("How many passports parsed? %d\n", newline);
    return valid;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        int partOne = parseInputDayOne(argv[i]);
        printf("How of them are valid? %d\n", partOne);
    }
    return 0;
}
