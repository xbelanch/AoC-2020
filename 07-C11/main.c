#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yastring.h"

#define MAXCHILDRENSIZE 32
#define MAXSIZELINE 512
#define MAXSIZERULES 1024

typedef struct child {
    char *name;
    int amount;
} Child;

typedef struct rule {
    char *key;
    Child *children[MAXCHILDRENSIZE];
} Rule;

Rule *rules[MAXSIZERULES];

Rule *lineToRule(char *line) {

    // create a blank rule
    Rule *rule = (Rule*)malloc(sizeof(Rule));

    size_t len = 0;

    // discard carriage return or new line
    strtok(line, "\r");
    strtok(line, "\n");

    // split input line by delimiter "contain "
    // in two strings: rule and container
    char *delimiter = "contain ";
    char *pch = strstr(line, delimiter);
    pch += strlen(delimiter);

    // get container
    char *container = malloc(sizeof(char) * strlen(pch) + 1);
    strncpy(container, pch, strlen(pch));
    container[strlen(container) - 1] = '\0'; // remove last dot

    // get key rule
    char *key = malloc(sizeof(char) * strlen(line) + 1);
    len = strlen(line) - strlen(pch) - strlen(delimiter);
    strncpy(key, line, len);
    key[len - 1] = '\0'; // remove last space

    // trim bag word from rule and container
    strremove(key, " bags");
    strremove(key, " bag");
    strremove(container, " bags");
    strremove(container, " bag");

    // assign key to rule
    rule->key = key;

    // split container in several entries or bags
    char *bag = malloc(sizeof(char) * MAXSIZELINE);
    int nchild = 0;
    while ((bag = strsplit(&container, ",")) != NULL) {
        if (bag[0] == ' ') {
            bag++;
        }

        if (strcmp(bag, "no other") == 0) {
            rule->children[0] = NULL;
            break;
        } else {
            // create a children
            Child *child = (Child*)malloc(sizeof(Child));

            // get amount of bags
            len = strlen(bag) - strlen(strstr(bag, " "));
            char *number = malloc(sizeof(char) * strlen(bag) + 1);
            strncpy(number, bag, len);
            number[len] = '\0';
            int amount = atoi(number);
            child->amount = amount;

            // get name of bags
            char *pstr = strstr(bag, " ");
            pstr++;

            // check if entry is the last one
            // @TODO: I don't know why last entry adds some extra characters at the end of the string
            char *dot = strstr(pstr, ".");
            if (dot != NULL) {
                len = strlen(pstr) - strlen(dot);
                char *color = malloc(sizeof(char) * strlen(pstr) + 1);
                strncpy(color, pstr, len);
                color[len] = '\0';
                child->name = color;
            } else {
                child->name = pstr;
            }

            // Add child to rule
            rule->children[nchild] = child;
            rule->children[nchild + 1] = NULL;
            nchild++;
        }
    }

    free(bag);
    return rule;
}

void printRule(Rule *rule) {
    printf("Rule> %s:\n", rule->key);
    if (rule->children[0] != 0) {
        for (int i = 0; rule->children[i] != NULL; i++)
            printf("  %d of %s\n", rule->children[i]->amount, rule->children[i]->name);
    } else {
        printf( "  contain no other bags\n");
    }
}

int solveFile(char *filepath) {
    printf("%s\n", filepath);

    FILE *fp = fopen(filepath, "r");

    if (fp == NULL) {
        perror("Failed: ");
        return 1;
    }

    printf("Processing %s...\n", filepath);

    char lines[MAXSIZELINE];
    int nrules = 0;
    while (fgets(lines, sizeof(lines), fp) != NULL) {
        rules[nrules] = lineToRule(lines);
        printRule(rules[nrules]);
        rules[nrules + 1] = NULL;
        nrules++;
    }

    printf("How many rules processed: %d\n", nrules);

    fclose(fp);

    return 0;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solveFile(argv[i]);
    }

    return 0;
}
