#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXLINEBUFFER 1024
#define MAXGROUPS 2048

typedef struct inputFile {
    int lines;
    char **input;
} InputFile;

typedef struct group {
    int people;
    int start;
    int end;
} Group;

InputFile g_inputFile;
Group* g_groups[MAXGROUPS];

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

    }

    fclose(fp);
}

Group *createGroup(int people, int start, int end) {
    Group *group = malloc(sizeof(Group));
    group->people = people;
    group->start = start;
    group->end = end;
    return group;
}

int checkNewGroup(char* string) {
    int result = 0;
    if (string[0] == '\n') {
        result = 1;
    }
    return result;
}

char *intersect(char *src, char *dst, int line) {

    // remove return carriage

    if (line > 0) {

        // intersect any occurrence between two strings
        // i.e
        // ab
        // ac
        // ->
        // a

        // we need a occurrences buffer
        char *occurrences = malloc(sizeof(char) * MAXLINEBUFFER);
        occurrences[0] = '\0';

        int match = 0;

        for (char *ptr_src = src; *ptr_src != '\0'; ptr_src++) {
            for (char *ptr_dst = dst; *ptr_dst != '\0'; ptr_dst++) {

                if (*ptr_src == *ptr_dst) {
                    match = 1;
                    break;
                }

                if (*ptr_src != *ptr_dst) {
                    match = 0;
                }
            }

            if (match) {
                size_t len = strlen(occurrences);
                char *buffer = malloc(sizeof(char) * len + 1 + 1);
                strcpy(buffer, occurrences);
                buffer[len] = *ptr_src;
                buffer[len + 1] = '\0';
                strcpy(occurrences, buffer);
                free(buffer);
                match = 0;
            }
        }

        return occurrences;

    } else {
        // first of all, remove return carriage
        if (src[strlen(src) - 1] == '\r' || src[strlen(src) - 1] == '\n')
            src[strlen(src) - 1] = '\0';

        // copy literally src to dst
        dst = malloc(sizeof(char) * strlen(src));
        dst[0] = '\0';
        // remove all the repeated occurrences
        // i.e: aaaaaabaaaacccaaabbb -> abc
        int match = 0;
        for (char *ptr_src = src; *ptr_src != '\0'; ptr_src++) {

            if (strlen(dst) == 0) {
                size_t len = strlen(dst);
                char *buffer = malloc(sizeof(char) * len + 1 + 1);
                buffer[len] = *ptr_src;
                buffer[len + 1] = '\0';
                strcpy(dst, buffer);
                free(buffer);
            }

            for (char *ptr_dst = dst; *ptr_dst != '\0'; ptr_dst++) {
                if (*ptr_src == *ptr_dst) {
                    match = 0;
                    break;
                }

                if (*ptr_src != *ptr_dst) {
                    match = 1;
                }
            }

            if (match) {
                size_t len = strlen(dst);
                char *buffer = malloc(sizeof(char) * len + 1 + 1);
                strcpy(buffer, dst);
                buffer[len] = *ptr_src;
                buffer[len + 1] = '\0';
                strcpy(dst, buffer);
                free(buffer);
                match = 0;
            }
        }
        /* printf("src: %s\n", src); */
        /* printf("dst: %s\n", dst); */
    }

    return dst;
}

int dumpGroupData(char** input) {
    char *yes_to_questions;

    int line =0;
    for (char **ptr = input; *ptr != NULL; ptr++) {
        yes_to_questions = intersect(*ptr, yes_to_questions, line);
        line++;
    }
    return (int) strlen(yes_to_questions);
}

int partTwo() {
    int total_yes_to_questions = 0;
    int group = 0;
    printf("Group :%d\n", group);
    group++;
    char** stackGroups = (char**)malloc(sizeof(char) * MAXGROUPS);
    int index = 0;
    for (int i = 0; i < g_inputFile.lines; i++) {
        if (g_inputFile.input[i][0] == '\n') { // check new line = group
            // set end of array of strings
            stackGroups[index] =NULL;
            // dump or processing data from stackGroups
            total_yes_to_questions += dumpGroupData(stackGroups);
            // reset index
            index = 0;

            /* printf("Group :%d\n", group); */
            group++;
        } else {
            stackGroups[index] = g_inputFile.input[i];
            /* printf(">%s", stackGroups[index]); */
            index++;
        }
    }
    // matching last group
    stackGroups[index] = NULL;
    total_yes_to_questions += dumpGroupData(stackGroups);
    index = 0;

    return total_yes_to_questions;
}

int collectQuestions(char *questions) {

    int occurrences = 0;
    char *match = malloc(sizeof(char) * MAXLINEBUFFER);
    match[0] = '\0';
    for (char* ptr = questions; *ptr != '\0'; ptr++) {
        for (char* src = match; *src != '\0'; src++) {
            if (*ptr == *src) {
                occurrences++;
            }
        }
        if (occurrences == 0 || strlen(match) == 0)  {
            size_t len = strlen(match);
            char *tmp = malloc(sizeof(char) * len + 1 + 1); // one for extra char, one for trailing zero
            tmp[len] = *ptr;
            tmp[len + 1] = '\0';
            strcpy(match, tmp);
            free(tmp);
        } else {
            occurrences = 0;
        }
    }

    /* printf("match> %s\n", match); */
    return strlen(match);
}


int partOne() {
    int solution = 0;
    // concat all the questions in one line
    char *questions = malloc(sizeof(char) * MAXLINEBUFFER);
    questions[0] = '\0';

    for (int i = 0; i < g_inputFile.lines; i++) {
        if (checkNewGroup(g_inputFile.input[i])) {
            solution += collectQuestions(questions);
            questions[0] = '\0';
        } else {
            strcat(questions, g_inputFile.input[i]);
            // remove return carriages
            char* ptr = questions + strlen(questions) - 1;
            *ptr = '\0';
        }
    }

    solution += collectQuestions(questions);
    free(questions);
    return solution;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc ; i++) {
        getInputData(argv[i]);
    }

    printf("Solution part one: %d\n", partOne());
    printf("Solution part two: %d\n", partTwo());

    return 0;
}
