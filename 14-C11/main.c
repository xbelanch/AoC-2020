#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE_LINES 2048
#define MAX_SIZE_CHARACTERS 512

int todo(){
    printf("TODO:\n");
    return 0;
}

int solve_file(char *filepath) {
    printf("%s\n", filepath);
    FILE *fp = fopen(filepath, "r");
    char chr;
    char buffer[MAX_SIZE_CHARACTERS];
    char lines[MAX_SIZE_LINES][MAX_SIZE_CHARACTERS];
    char *ptr = buffer;
    int num = 0;

    // read and store the input file
    while (1) {
        chr = fgetc(fp);
        if (feof(fp))
            break;
        if (chr == '\n') {
            *ptr = '\0';
            strcpy(lines[num++], buffer);
            ptr = buffer;

        } else {
            *ptr++ = chr;
        }
    }

    // print to stdout
    for (int i = 0; i < num; i++) {
        fprintf(stdout, "line[%d]: %s\n", i, lines[i]);
    }

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
