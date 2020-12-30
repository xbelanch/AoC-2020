#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINEBUFFER 1024
#define MAXGROUPS 1024

int any_yesu(char **answers) {
    char* result = (char*)malloc(sizeof(char) * MAXLINEBUFFER);
    result[0] = '\0';

    int i = 0;
    int match = 0;
    for (char **answer = answers; *answer != NULL; answer++) {
        // remove return carriages
        char* rc = *answer + strlen(*answer) - 1;
        *rc = '\0';

        for (char *chr = *answer; *chr != '\0'; chr++) {
            if (strlen(result) == 0) {
                result[i] = *chr;
                result[i + 1] = '\0';
                i++;
            } else {
                for (char *x = result; *x != '\0'; x++ ) {
                    if (*chr == *x) {
                        match++;
                    }
                }
                if (!match ) {
                    result[i] = *chr;
                    result[i + 1] = '\0';
                    i++;
                }
                match = 0;
            }
        }
    }

    int len = strlen(result);
    return len;
}

int every_yesu(char **answers) {
    char* result = (char*)malloc(sizeof(char) * MAXLINEBUFFER);
    result[0] = '\0';

    int i = 0;
    int match = 0;
    int people = 0;

    // concatenate all the answers in one line
    for (char **answer = answers; *answer != NULL; answer++) {
        for (char *chr = *answer; *chr != '\0'; chr++) {
                result[i] = *chr;
                result[i + 1] = '\0';
                i++;
        }
        people++;
    }

    // simplest solution is almost always the best solution
    int k = 0;
    char* buffer = (char*)malloc(sizeof(char) * MAXLINEBUFFER);
    buffer[0] = '\0';

    for (int i = 0; i < (int)strlen(result); i++) {
        for (int j = 0; j < (int)strlen(result); j++) {
            if (result[i] == result[j]) {
                match++;
            }
        }
        if ((match / people) > 0) {
            buffer[k] = result[i];
            buffer[k + 1] = '\0';
            k++;
        }
        match = 0;
    }

    // remove all repeated occurrences of same character
    result[0] = '\0';
    strcpy(result, buffer);
    buffer[0] = '\0';
    k = 0;
    match = 0;
    for (int i = 0; i < (int)strlen(result); i++) {
        if (strlen(buffer) == 0) {
            buffer[k] = result[i];
            buffer[k + 1] = '\0';
            k++;
        } else {
            for (int j = 0; j < (int)strlen(buffer); j++) {
                if (result[i] == buffer[j]) {
                    match++;
                }
            }
            if (!match) {
                buffer[k] = result[i];
                buffer[k + 1] = '\0';
                k++;
            }
            match = 0;
        }
    }

    result = buffer;
    int len = strlen(result);
    return len;
}

void solve_file(char *filename)
{
    FILE *fp;
    char** lines;
    char** answers;
    int nlines = 0;
    int any_result = 0;
    int every_result = 0;

    // count all the lines from input file
    fp = fopen(filename, "r");
    // But please note: Why is “while ( !feof (file) )” always wrong?
    // https://stackoverflow.com/questions/5431941/why-is-while-feof-file-always-wrong
    while(!feof(fp)) {
        char ch = fgetc(fp);
        if(ch == '\n') {
            nlines++;
        }
    }
    fclose(fp);

    // store the content of lines
    lines = (char **) malloc(sizeof(char*) * nlines);

    // initialize answers
    answers = (char **)malloc(sizeof(char) * MAXGROUPS);

    fp = fopen(filename, "r");

    int i = 0;
    for (int currentLineIndex = 0; currentLineIndex < nlines; currentLineIndex++) {

        lines[currentLineIndex] = (char *) malloc(MAXLINEBUFFER + 1);
        fgets(lines[currentLineIndex], MAXLINEBUFFER, fp);

        // remove return carriage
        char *src, *dst;
        for (src = dst = lines[currentLineIndex]; *src != '\0'; src++) {
            *dst = *src;
            if (*dst != '\r' || *dst != '\n') dst++;
        }
        *dst = '\0';

        if (lines[currentLineIndex][0] != '\n') {
            answers[i] = lines[currentLineIndex];
            i++;
        } else {
            answers[i] = NULL;
            any_result += any_yesu(answers);
            every_result += every_yesu(answers);
            i = 0;
        }
    }

    answers[i] = NULL;
    any_result += any_yesu(answers);
    every_result += every_yesu(answers);

    printf("Puzzle input file: %s\n", filename);
    printf("Part 1: %d\n", any_result);
    printf("Part 2: %d\n", every_result);

    fclose(fp);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc ; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
