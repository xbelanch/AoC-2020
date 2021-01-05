#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yastring.h"

#define MAXCHILDRENSIZE 32
#define MAXSIZELINE 512
#define MAXSIZERULES 1024
#define MAXSIZECOLORS 1024

typedef struct child {
    char *name;
    int amount;
    struct rule *rule;
} Child;

typedef struct rule {
    char *key;
    Child *children[MAXCHILDRENSIZE];
} Rule;

// Global variables
Rule *rules[MAXSIZERULES];
char *colors[MAXSIZECOLORS];
int ncolors;

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
            return rule;
        } else {
            // create a children
            Child *child = (Child*)malloc(sizeof(Child));
            child->rule = rule;

            // get amount of bags
            len = strlen(bag) - strlen(strstr(bag, " "));
            char *number = malloc(sizeof(char) * MAXSIZELINE);
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
                char *color = malloc(sizeof(char) * MAXSIZELINE);
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

void printPrettyRules(Rule *rule) {
    printf("Rule> %s:\n", rule->key);
    if (rule->children[0] != 0) {
        for (int i = 0; rule->children[i] != NULL; i++)
            printf("  %d of %s\n", rule->children[i]->amount, rule->children[i]->name);
    } else {
        printf( "  contain no other bags\n");
    }
}

void rulesFromFile(char *filepath) {
    FILE *fp = fopen(filepath, "r");

    if (fp == NULL) {
        perror("Failed: ");
        exit(0);
    }

    char lines[MAXSIZELINE];
    int nrules = 0;
    while (fgets(lines, sizeof(lines), fp) != NULL) {
        rules[nrules] = lineToRule(lines);
        rules[nrules + 1] = NULL;
        nrules++;
    }

    fclose(fp);
 }

void printGraphvizOfRules() {
    printf("digraph Rules {\n");
    for (int i = 0 ; rules[i] != NULL; i++) {
        if (rules[i]->children[0] != NULL) {
            for (int j = 0; rules[i]->children[j] != NULL; j++) {
                printf("\t\"%s\" -> \"%s\";\n", rules[i]->key, rules[i]->children[j]->name);
            }
        } else {
            printf("\t\"%s\" -> \"no bags\";\n", rules[i]->key);
        }
    }
    printf("}\n");
}

Child **findContainers(char *color) {
    Child **containers = (Child**)malloc(sizeof(Child) * 512);
    int count = 0;
    containers[count] = NULL;

    for (int i = 0 ; rules[i] != NULL; i++) {
        if (rules[i]->children[0] != NULL) {
            for (int j = 0; rules[i]->children[j] != NULL; j++) {
                if (strcmp(rules[i]->children[j]->name, color) == 0) {
                    containers[count] = *(rules[i]->children);
                    containers[count + 1] = NULL;
                    count++;
                }
            }
        }
    }

    return containers;
}

void countWays (char *color) {
    colors[ncolors] = color;
    colors[ncolors + 1] = NULL;
    ncolors++;

    Child **containers = findContainers(color);

    int len = 0;
    while (containers[len] != NULL) {
        len++;
    }
    if (len > 0) {
        for (int i = 0; i < len; i++) {
            countWays(containers[i]->rule->key);
        }
    }
}


int solveFile(char *filepath) {
    rulesFromFile(filepath);
    /* printGraphvizOfRules(); */
    char *start = "shiny gold";
    ncolors = 0;
    colors[ncolors] = NULL;

    // recursive function to count ways from start color to rule color
    countWays(start);

    // how many colors has been collected?
    int lencolors = 0;
    while (colors[lencolors] != NULL) {
        lencolors++;
    }


    // remove duplicate colors
    int count = 0;
    char* tmp[MAXSIZECOLORS];
    int d;
    for (int c = 0; c < lencolors; c++) {
        for (d = 0; d < count; d++) {
            if(strcmp(colors[c], tmp[d]) == 0)
                break;
        }
        if (d == count) {
            tmp[count] = colors[c];
            count++;
        }
    }

    // remove one because star color not count
    return count - 1;
}


int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        printf("Input puzzle: %s\n", argv[i]);
        int partOne = solveFile(argv[i]);
        printf("Part one solution: %d\n", partOne);
    }
    return 0;
}
