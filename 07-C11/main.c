#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_LINE 512
#define MAX_BUFFER_SIZE 2048

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
            // parse every line, splitting string into tokens
            // and store onto buffer
            char *pch = strtok(lines[i], ",.\r\n");
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

    // print buffer to stdout
    int i = 0;
    for (char** ptr = buffer; *ptr != NULL; ptr++) {
        printf("buffer[%d]: %s\n", i, *ptr);
        i++;
    }

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
