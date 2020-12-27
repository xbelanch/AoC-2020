#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXLINEBUFFER 512
#define MAXGROUPS 1024

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


void printInput() {
    for (int i = 0; i < g_inputFile.lines; i++) {
        if (checkNewGroup(g_inputFile.input[i])) {
            printf("New group here\n");
        } else {
            printf("%d> %s", i, g_inputFile.input[i]);
        }
    }
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

void printGroups(/* int countGroups */)
{
    // WHAT THE FUCK!
    Group **ptr = g_groups;
    while(*ptr != NULL) {
        printf("---- People %d\n", (*ptr)->people);
        for (int i = (*ptr)->start; i < (*ptr)->end; i++) {
            printf(">%s\n", g_inputFile.input[i]);
        }
        ptr++;
    }

}

int partTwo()
{
    int solution = 0;
    int people = 0;
    int countGroups = 0;
    int start = 0;
    int end = 0;

    // time to capture people - answers
    for (int i = 0; i < g_inputFile.lines; i++) {
        if (checkNewGroup(g_inputFile.input[i])) {
            // from the last group
            g_groups[countGroups] = createGroup(people, start, end);
            start = end;
            // stupid hack to manage new lines
            start++;
            end++;

            people = 0;
            countGroups++;
        } else {
            people++;
            end++;
        }
    }
    printf("People involved: %d\n", people);
    g_groups[countGroups] = createGroup(people, start, end);
    countGroups++;

    printGroups(countGroups);


    return solution;
}



int main(int argc, char *argv[])
{
    for (int i = 1; i < argc ; i++) {
        getInputData(argv[i]);
    }
    /* printf("Solution part one: %d\n", partOne()); */
    printf("Solution part two: %d\n", partTwo());

    return 0;
}
