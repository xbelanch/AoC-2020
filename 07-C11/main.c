#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_LINE 512
#define MAX_BUFFER_SIZE 2048
#define MAX_BUFFER_RULES 1024

typedef struct rule {
    char *bagname;
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
    tmp[len + 1] = '\0';
    return tmp;
}

void solve_file(char* filename) {

    FILE *fp = fopen(filename, "r");
    int max = countlines(filename);
    char **lines = (char**)malloc(sizeof(char*) * max);
    char **buffer = (char**)malloc(sizeof(char*) * MAX_BUFFER_SIZE);

    printf("Filename: %s\n", filename);
    printf("Number of lines of %s file: %d\n", filename, max);

    // store all the lines from input filename to lines var
    for (int i, j =  0; i < max; i++) {
        lines[i] = (char *)malloc(MAX_BUFFER_LINE);
        if (fgets(lines[i], MAX_BUFFER_LINE + 1, fp) == NULL) {
            printf("ERROR, line too long at %d\n", i);
        } else {
            // parse every line, splitting string by commas
            // and store onto buffer
            char *pch = strtok(lines[i], ",.\r\n");

            // get name of the bag rule
            rules[i].bagname = getBagName(pch);
            rules[i + 1].bagname = NULL;

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
            buffer[j + 1] = NULL;
        }
    }

    for (int i = 0; rules[i].bagname != NULL; i++) {
        printf("%d>%s\n", i, rules[i].bagname);
    }

    // print buffer to stdout
    /* int i = 0; */
    /* for (char** ptr = buffer; *ptr != NULL; ptr++) { */
    /*     printf("buffer[%d]: %s\n", i, *ptr); */
    /*     i++; */
    /* } */

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
