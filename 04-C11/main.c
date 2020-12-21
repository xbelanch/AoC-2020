#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXBUFFER 2048
#define LINE_SIZE 256

int validate(char *field, char *value)
{
    // now switch option, buddy
    // https://stackoverflow.com/questions/4014827/how-can-i-compare-strings-in-c-using-a-switch-statement
    int year;
    int height;
    if (strcmp(field, "byr") == 0) {
        year = atoi(value);
        if (year >= 1920 && year <= 2002) {
            return 1;
        } else {
            return 0;
        }
    } else if (strcmp(field, "iyr") == 0) {
        year = atoi(value);
        if (year >= 2010 && year <= 2020) {
            return 1;
        } else {
            return 0;
        }
    } else if (strcmp(field, "eyr") == 0) {
        year = atoi(value);
        if (year >= 2020 && year <= 2030) {
            return 1;
        } else {
            return 0;
        }
    } else if (strcmp(field, "hgt") == 0) {
        // check first if cm or in is on it
        int len = strlen(value);
        const char *last_two = &value[len-2];
        if (!strcmp("cm", last_two))  {
            // remove the cm part
            char *tmp = strchr(value, 'c');
            *tmp = '\0';
            height = atoi(value);
            if (height >= 150 && height <= 193) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }

        if (!strcmp("in", last_two)) {
            // remove the in part
            char *tmp = strchr(value, 'i');
            *tmp = '\0';
            height = atoi(value);
            if (height >= 59 && height <= 76) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else if (strcmp(field, "hcl") == 0) {
        if (value[0] != '#') {
            return 0;
        } else {
            // check if six characters are 0-9 or a-f
            for (int i = 1; value[i] != '\0'; i++) {
                if (value[i] == '0' ||
                    value[i] == '1' ||
                    value[i] == '2' ||
                    value[i] == '3' ||
                    value[i] == '4' ||
                    value[i] == '5' ||
                    value[i] == '6' ||
                    value[i] == '7' ||
                    value[i] == '8' ||
                    value[i] == '9' ||
                    value[i] == 'a' ||
                    value[i] == 'b' ||
                    value[i] == 'c' ||
                    value[i] == 'd' ||
                    value[i] == 'e' ||
                    value[i] == 'f') {
                    continue;
                } else {
                    return 0;
                }
            }
            return 1;
        }
    } else if (strcmp(field, "ecl") == 0) {
        if (!strcmp(value, "amb") ||
            !strcmp(value, "blu") ||
            !strcmp(value, "brn") ||
            !strcmp(value, "gry") ||
            !strcmp(value, "grn") ||
            !strcmp(value, "hzl") ||
            !strcmp(value, "oth")) {
            return 1;
        } else {
            return 0;
        }
    } else if (strcmp(field, "pid") == 0) {
        if (strlen(value) == 9) {
            return 1;
        } else {
            return 0;
        }
    } else if (strcmp(field, "cid") == 0) {
        return 1;
    }
    return -1;
}

int validateField(char* field)
{
    if (strcmp(field, "byr") == 0 ||
        strcmp(field, "iyr") == 0 ||
        strcmp(field, "eyr") == 0 ||
        strcmp(field, "hgt") == 0 ||
        strcmp(field, "hcl") == 0 ||
        strcmp(field, "ecl") == 0 ||
        strcmp(field, "pid") == 0) {
        return 1;
    } else {
        return 0;
    }
}

// https://stackoverflow.com/questions/35178520/how-to-read-parse-input-in-c-the-faq
int parseInputDayOne(char* filename) {

    FILE* fp = fopen(filename, "rb");

    if (!fp)
        fprintf(stderr, "Cannot open %s: %s\n", filename, strerror(errno));

    char *fileBuffer = malloc(sizeof(char) * LINE_SIZE);
    char *tmpBuffer = malloc(sizeof(char) * LINE_SIZE * 2);
    char passports[1024][LINE_SIZE * 2];
    int id = 0;
    // initialize tmpBuffer
    tmpBuffer[0] = '\0';
    // reads the stream from in
    while (fgets(fileBuffer, LINE_SIZE, fp) != NULL) {
        if (fileBuffer[0] != '\r') {
            // remove new line
            fileBuffer[strcspn(fileBuffer, "\r")] = 0;
            // M-S-/ expansion of the word!
            // concatenate the strings
            strcat(tmpBuffer, fileBuffer);
            // add simple space
            strcat(tmpBuffer, " ");
        } else {
            strcpy(passports[id], tmpBuffer);
            id++;
            tmpBuffer[0] = '\0';
        }
    }

    // copy last passport entry
    strcpy(passports[id], tmpBuffer);
    id++;

    // free memory
    free(fileBuffer);
    free(tmpBuffer);

    int validPassports = 0;
    for (int i = 0; i < id; i++) {
        printf("%d>%s\n", i, passports[i]);

        // get fields and validate
        char *pair;
        char *ptr;
        int len = 0;
        int tmp = 0;
        int sum = 0;
        // extract pairs from every passport entry
        for (;;) {
            ptr = passports[i] + tmp; //

            if (*ptr == '\0') break;

            len = strcspn(ptr, " ");
            tmp += len;

            pair = malloc(sizeof(char) * len);
            pair[len] = '\0';

            strncpy(pair, ptr, len);

            // validate field
            char *field = malloc(sizeof(char) * 3);
            field[3] = '\0';
            strncpy(field, pair, 3);
            /* printf(">%s\n", field); */
            sum += validateField(field);

            tmp++;
        }
        if (sum > 6) {
            printf("Passport fields are valid\n");
            validPassports++;
        } else {
            printf("Passport fields are NOT valid\n");
        }

        sum = 0;
    }

    printf("Valid passports: %d\n", validPassports);

    /* while ( fgets(buffer, MAXBUFFER, fp) != NULL) { */

    /*     if (buffer[0] != '\r' && buffer[1] != '\n' ) { */
    /*         // Truncate lines */
    /*         passports[newline] = malloc(sizeof(char) * 256); */
    /*         /\* for (char *p = strtok(buffer, "\r\n"); p; p = strtok(NULL, "\r\n")) { *\/ */
    /*                 /\* for (char *r = strtok(q, " "); r; r = strtok(NULL, " ")) { *\/ */
    /*                 /\*     // get the field *\/ */
    /*                 /\*     char* field = malloc(sizeof(char) * 3); *\/ */
    /*                 /\*     strncpy(field, r, 3); *\/ */
    /*                 /\*     /\\* printf("Field: %s\n", field); *\\/ *\/ */

    /*                 /\*     // get the value *\/ */
    /*                 /\*     char *tmp = strchr(r, ':'); *\/ */
    /*                 /\*     char *value = malloc(sizeof(char) * 16); *\/ */
    /*                 /\*     memcpy(value, tmp + 1, 16); *\/ */

    /*                 /\*     // Validate if all the fields are present on passport *\/ */
    /*                 /\*     cntflds += validateField(field); *\/ */

    /*                 /\*     /\\* // Finally we validate every field depending on its value *\\/ *\/ */
    /*                 /\*     if (!validate(field, value)) { *\/ */
    /*                 /\*         notvalid = 1; *\/ */
    /*                 /\*         break; *\/ */
    /*                 /\*     } *\/ */
    /*                 /\* } *\/ */
    /*         /\* } *\/ */
    /*     } else { */
    /*         newline++; */
    /*         printf("\nPassport %d:\n", newline); */
    /*         // check if passport is valid at all */
    /*         if (cntflds == 7 && !notvalid) valids++; */
    /*         // reset temporal variables */
    /*         cntflds = 0; */
    /*         notvalid = 0; */
    /*     } */
    /* } */
    // last passport of the input
    /* if (cntflds == 7 && !notvalid) valids++; */

    fclose(fp);

    /* printf("\nHow many passports parsed? %d\n", newline); */

    /* // print passports */
    /* for (int i = 0; i < newline; i++) { */
    /*     printf("p%d> %s\n", i, passports[i]); */
    /* } */

    return 0;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        int partTwo = parseInputDayOne(argv[i]);
        /* printf("How of them are valid? %d\n", partTwo); */
    }
    return 0;
}
