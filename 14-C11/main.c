#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_LINES 1024

typedef struct line {
    char* text;
} Line;

Line lines[MAX_SIZE_LINES];

int parse_input_file(int size_lines) {
    for (int i = 0; i < size_lines; ++i) {
            fprintf(stdout, "%u: %s\n", i, lines[i].text);
    }
    return 0;
}

int input_file(char *filename){
    int error = -1;
    printf("Open file: %s\n", filename);
    FILE *input_file = fopen(filename, "rb");

    if (NULL == input_file) {
        fprintf(stderr, "File %s didn't found!\n", filename);
        return error;
    }

    int c = fgetc(input_file);
    char* string = (char *)malloc(sizeof(char) * 512);
    size_t i = 0;
    int nline = 0;

    while (EOF != c) {
        string[i++] = c;
        if ('\n' == c) {
            string[i-1] = '\0';
            size_t len = strlen(string);
            lines[nline].text = (char *)malloc(sizeof(char) * len);
            memcpy(lines[nline].text, string, len);
            i = 0; nline++;
            string[i] = '\0';
        }
        c = fgetc(input_file);
    }

    parse_input_file(nline);

    int success = fclose(input_file);
    return success;
}


int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        input_file(argv[i]);
    }
    return 0;
}
