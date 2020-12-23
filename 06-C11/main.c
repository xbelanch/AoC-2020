#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXLINEBUFFER 128

typedef struct inputFile {
    int lines;
    char **input;
} InputFile;

InputFile g_inputFile;

void getInputData(char *filename)
{
    printf("%s\n", filename);


    // initialize
    g_inputFile.lines = 0;
    g_inputFile.input = NULL;


    // Count lines from file
    FILE *fp;
    fp = fopen(filename, "r");

    // But please note: Why is “while ( !feof (file) )” always wrong?
    // https://stackoverflow.com/questions/5431941/why-is-while-feof-file-always-wrong
    while(!feof(fp)) {
        char ch = fgetc(fp);
        if(ch == '\n') {
            g_inputFile.lines++;
        }
    }

    fclose(fp);

    // store the content of lines
    g_inputFile.input = (char **) malloc(sizeof(char*) * g_inputFile.lines);

    fp = fopen(filename, "r");

    for (int currentLineIndex = 0; currentLineIndex < g_inputFile.lines; currentLineIndex++) {

        g_inputFile.input[currentLineIndex] = (char *) malloc(MAXLINEBUFFER + 1);
        fgets(g_inputFile.input[currentLineIndex], MAXLINEBUFFER, fp);

        // remove return carriage
        char *src, *dst;
        for (src = dst = g_inputFile.input[currentLineIndex]; *src != '\0'; src++) {
            *dst = *src;
            if (*dst != '\r') dst++;
        }
        *dst = '\0';

        g_inputFile.input[currentLineIndex];
    }

    fclose(fp);
}

void printInput() {
    for (int i = 0; i < g_inputFile.lines; i++) {
        printf("%d> %s", i, g_inputFile.input[i]);
    }
}


int main(int argc, char *argv[])
{
    for (int i = 1; i < argc ; i++) {
        getInputData(argv[i]);
    }
    printInput();
    return 0;
}
