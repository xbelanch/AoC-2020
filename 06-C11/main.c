#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXLINEBUFFER 1024
#define MAXGROUPS 1024

/* char *intersect(char *src, char *dst, int line) { */

/*     // remove return carriage */

/*     if (line > 0) { */

/*         // intersect any occurrence between two strings */
/*         // i.e */
/*         // ab */
/*         // ac */
/*         // -> */
/*         // a */

/*         // we need a occurrences buffer */
/*         char *occurrences = malloc(sizeof(char) * MAXLINEBUFFER); */
/*         occurrences[0] = '\0'; */

/*         int match = 0; */

/*         for (char *ptr_src = src; *ptr_src != '\0'; ptr_src++) { */
/*             for (char *ptr_dst = dst; *ptr_dst != '\0'; ptr_dst++) { */

/*                 if (*ptr_src == *ptr_dst) { */
/*                     match = 1; */
/*                     break; */
/*                 } */

/*                 if (*ptr_src != *ptr_dst) { */
/*                     match = 0; */
/*                 } */
/*             } */

/*             if (match) { */
/*                 size_t len = strlen(occurrences); */
/*                 char *buffer = malloc(sizeof(char) * len + 1 + 1); */
/*                 strcpy(buffer, occurrences); */
/*                 buffer[len] = *ptr_src; */
/*                 buffer[len + 1] = '\0'; */
/*                 strcpy(occurrences, buffer); */
/*                 free(buffer); */
/*                 match = 0; */
/*             } */
/*         } */

/*         return occurrences; */

/*     } else { */
/*         // first of all, remove return carriage */
/*         if (src[strlen(src) - 1] == '\r' || src[strlen(src) - 1] == '\n') */
/*             src[strlen(src) - 1] = '\0'; */

/*         // copy literally src to dst */
/*         dst = malloc(sizeof(char) * strlen(src)); */
/*         dst[0] = '\0'; */
/*         // remove all the repeated occurrences */
/*         // i.e: aaaaaabaaaacccaaabbb -> abc */
/*         int match = 0; */
/*         for (char *ptr_src = src; *ptr_src != '\0'; ptr_src++) { */

/*             if (strlen(dst) == 0) { */
/*                 size_t len = strlen(dst); */
/*                 char *buffer = malloc(sizeof(char) * len + 1 + 1); */
/*                 buffer[len] = *ptr_src; */
/*                 buffer[len + 1] = '\0'; */
/*                 strcpy(dst, buffer); */
/*                 free(buffer); */
/*             } */

/*             for (char *ptr_dst = dst; *ptr_dst != '\0'; ptr_dst++) { */
/*                 if (*ptr_src == *ptr_dst) { */
/*                     match = 0; */
/*                     break; */
/*                 } */

/*                 if (*ptr_src != *ptr_dst) { */
/*                     match = 1; */
/*                 } */
/*             } */

/*             if (match) { */
/*                 size_t len = strlen(dst); */
/*                 char *buffer = malloc(sizeof(char) * len + 1 + 1); */
/*                 strcpy(buffer, dst); */
/*                 buffer[len] = *ptr_src; */
/*                 buffer[len + 1] = '\0'; */
/*                 strcpy(dst, buffer); */
/*                 free(buffer); */
/*                 match = 0; */
/*             } */
/*         } */
/*         /\* printf("src: %s\n", src); *\/ */
/*         /\* printf("dst: %s\n", dst); *\/ */
/*     } */

/*     return dst; */
/* } */

/* int dumpGroupData(char** input) { */
/*     char *yes_to_questions; */

/*     int line =0; */
/*     for (char **ptr = input; *ptr != NULL; ptr++) { */
/*         yes_to_questions = intersect(*ptr, yes_to_questions, line); */
/*         line++; */
/*     } */
/*     return (int) strlen(yes_to_questions); */
/* } */

/* int partTwo() { */
/*     int total_yes_to_questions = 0; */
/*     int group = 0; */
/*     printf("Group :%d\n", group); */
/*     group++; */
/*     char** stackGroups = (char**)malloc(sizeof(char) * MAXGROUPS); */
/*     int index = 0; */
/*     for (int i = 0; i < g_inputFile.lines; i++) { */
/*         if (g_inputFile.input[i][0] == '\n') { // check new line = group */
/*             // set end of array of strings */
/*             stackGroups[index] =NULL; */
/*             // dump or processing data from stackGroups */
/*             total_yes_to_questions += dumpGroupData(stackGroups); */
/*             // reset index */
/*             index = 0; */

/*             /\* printf("Group :%d\n", group); *\/ */
/*             group++; */
/*         } else { */
/*             stackGroups[index] = g_inputFile.input[i]; */
/*             /\* printf(">%s", stackGroups[index]); *\/ */
/*             index++; */
/*         } */
/*     } */
/*     // matching last group */
/*     stackGroups[index] = NULL; */
/*     total_yes_to_questions += dumpGroupData(stackGroups); */
/*     index = 0; */

/*     return total_yes_to_questions; */
/* } */


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
                if (!match) {
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
    for (char **answer = answers; *answer != NULL; answer++) {
        /* printf("%s", *answer); */
    }

    return 0;
}

void solve_file(char *filename)
{
    FILE *fp;
    char** lines;
    int nlines = 0;
    char** answers;
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
