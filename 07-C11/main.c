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
            printf("%s contain %d unknow bag\n", rules[i].name, rules[i].bags[0]->number);
        }
    }
}

void solve_file(char* filename) {

    FILE *fp = fopen(filename, "r");
    int max = countlines(filename);
    char **lines = (char**)malloc(sizeof(char*) * max);
    char **buffer = (char**)malloc(sizeof(char*) * MAX_BUFFER_SIZE);

    printf("Filename: %s\n", filename);
    printf("Number of lines of %s file: %d\n", filename, max);

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
                nbags++;
            }

            int k = 0;
            while (pch != NULL) {
                buffer[j + k] = malloc(sizeof(char) * strlen(pch) + 1);
                buffer[j + k][0] = '\0';
                memcpy(buffer[j + k], pch, strlen(pch));
                buffer[j + k][strlen(pch)] = '\0';
                pch = strtok(NULL, ",.\r\n");

                k++;
            }
            j += k;
            nbags = 0;
            buffer[j + 1] = NULL;
        }
    }

    // Naif Tranversal Tree of Rules
    transverseTreeRules();

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
