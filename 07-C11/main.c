#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_LINE 512
#define MAX_BUFFER_SIZE 2048
#define MAX_BUFFER_RULES 1024
#define MAX_BUFFER_BAGS 32

typedef struct bag {
    char *bagname;
    int number;
} Bag;

typedef struct rule {
    char *name;
    Bag *bags[MAX_BUFFER_BAGS]; // we don't know how exactly bags contains every rule
} Rule;

Rule rules[MAX_BUFFER_RULES];

int countlines(char *filename){
    int lines = 0;
    FILE* fp = fopen(filename, "r");

    while(!feof(fp)) {
        char ch = fgetc(fp);
        if(ch == '\n') {
            lines++;
        }
    }
    fclose(fp);
    return lines;
}

int getNumberBags(char *string, int spaces) {
    char number[1];
    char *ptr1, *ptr2;
    int count = 0;
    for (ptr1 = ptr2 = string; *ptr1 != '\0'; ptr1++) {
        if (*ptr1 == ' ')
            count++;
        if (count == spaces) {
            ptr2 = ptr1;
            if (*ptr2 == 'n' && *(ptr2++) == 'o')
                return 0;
        }
    }
    number[0] = *ptr2;
    number[1] = '\0';

    return atoi(number);
}

char *getContainBag(void) {

    char *tmp = malloc(sizeof(char) * MAX_BUFFER_LINE);

    return tmp;
}

char *getBagName2(char *string, int from, char sdelimiter, int to, char edelimiter) {
    char *bagname = malloc(sizeof(char) * MAX_BUFFER_LINE);
    char *sptr, *eptr;
    int scount, ecount = 0;
    int flag = 0;
    for (eptr = string; *eptr != '\0'; eptr++) {
        if (ecount == to) {
            eptr--; // remove last end delimiter
            break;
        }

        if (*eptr == edelimiter && flag) {
            ecount++;
        }

        if (scount == from && !flag) {
            sptr = eptr;

            flag = 1;
        }

        if (*eptr == sdelimiter)
            scount++;
    }

    for (int i = 0; sptr != eptr; i++) {
        bagname[i] = *sptr;
        bagname[i + 1] = '\0';
        sptr++;
    }

    return bagname;
}

char *getBagName(char *string) {
    char *tmp = malloc(sizeof(char) * MAX_BUFFER_LINE);
    tmp[0] = '\0';
    int spaces = 0;
    int len = 0;
    for (char *ptr = string; *ptr != '\0'; ptr++) {
        if (*ptr == ' ') {
            spaces++;
        }
        if (spaces == 2) {
            memcpy(tmp, string, len + 1);
            break;
        }
        len++;
    }
    tmp[len] = '\0';
    return tmp;
}

void transverseTreeRules(void) {
    for (int i = 0; rules[i].name != NULL; i++) {
        if (rules[i].bags[0] == NULL) {
            printf("%s contain no other bags\n", rules[i].name);
        } else {
            printf("%s contain %d %s bag(s)", rules[i].name, rules[i].bags[0]->number, rules[i].bags[0]->bagname);

            if (rules[i].bags[1] != NULL) {
                int j = 1;
                while (rules[i].bags[j] != NULL) {
                    printf(" and %d %s bag(s)", rules[i].bags[j]->number, rules[i].bags[j]->bagname);
                    j++;
                }
                printf("\n");
            } else {
                printf("\n");
            }
        }
    }
}

void findAllOccurrencesByBagName(char* bagname) {
    printf("Find all occurrences of %s bag\n", bagname);
    for (int i = 0; rules[i].name != NULL; i++) {
        if (strcmp(rules[i].name, bagname) == 0)
            printf("Matched at line %d as rule\n", i + 1);
        if (rules[i].bags[0] != NULL) {
            for (int j = 0; rules[i].bags[j] != NULL; j++) {
                if (strcmp(rules[i].bags[j]->bagname, bagname) == 0) {
                    printf("Matched at line %d\n", i + 1);
                }
            }
        }
    }
}

void solve_file(char* filename) {

    FILE *fp = fopen(filename, "r");
    int max = countlines(filename);
    char **lines = (char**)malloc(sizeof(char*) * max);
    char **buffer = (char**)malloc(sizeof(char*) * MAX_BUFFER_SIZE);

    printf("File %s: %d lines\n", filename, max);

    // store all the lines from input filename to lines var
    int nbags = 0;
    for (int i, j =  0; i < max; i++) {
        lines[i] = (char *)malloc(MAX_BUFFER_LINE);
        if (fgets(lines[i], MAX_BUFFER_LINE + 1, fp) == NULL) {
            printf("ERROR, line too long at %d\n", i);
        } else {
            // parse every line, splitting string by commas
            // and store it into buffer
            char *pch = strtok(lines[i], ",.\r\n");

            // get name of the bag rule
            rules[i].name = getBagName(pch);
            rules[i + 1].name = NULL;

            // get number of bags (first pass)
            int number = getNumberBags(pch, 4);
            if (number == 0) {
                rules[i].bags[0] = NULL;
            } else {
                rules[i].bags[nbags] = malloc(sizeof(Bag));
                rules[i].bags[nbags]->number = number;
                rules[i].bags[nbags]->bagname =getBagName2(pch, 5, ' ', 2, ' ');
                nbags++;
            }

            int k = 0;
            while (pch != NULL) {
                pch = strtok(NULL, ",.\r\n");
                if (pch != NULL) {
                    // remove first character if this equals to space
                    if (pch[0] == ' ')
                        pch++;
                    char *tmp = strdup(pch);
                    // add new bag to container
                    rules[i].bags[nbags] = malloc(sizeof(Bag));
                    rules[i].bags[nbags]->number = atoi(getBagName2(tmp, 0, ' ', 1, ' '));
                    rules[i].bags[nbags]->bagname = getBagName2(tmp, 2, ' ', 2, ' ');
                    nbags++;
                }

                k++;
            }
            j += k;
            buffer[j + 1] = NULL;
            nbags++;
            rules[i].bags[nbags] = NULL;
            nbags = 0;

        }
    }
    // Naif Tranversal Tree of Rules
    /* transverseTreeRules(); */
    findAllOccurrencesByBagName("shiny gold");

    free(lines);
    free(buffer);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
