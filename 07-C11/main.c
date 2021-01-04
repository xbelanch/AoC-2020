#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHILDRENSIZE 32

typedef struct child {
    char *name;
    int amount;
} Child;

typedef struct rule {
    char *name;
    Child children[MAXCHILDRENSIZE];
} Rule;

Rule lineToRule(char *line) {
    Rule rule = {
        "u pogger",
        {{"mate", 1 }}
    };
    return rule;
}

void solveFile(char *filepath) {
    printf("%s\n", filepath);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solveFile(argv[i]);
    }
    return 0;
}
