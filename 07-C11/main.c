#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yastring.h"

#define MAXSIZELINES 2048

typedef struct child {
    char *color;
    int amount;
    struct child *next;
} Child;

typedef struct rule {
    char *color;
    struct child *contain;
    struct rule *next;
} Rule;

typedef struct container {
    char *color;
    int amount;
    char *rule;
    struct container *next;
} Container;

typedef struct visited {
    char *color;
    struct visited *next;
} Visited;

Rule *createNewRule(char *color) {
    Rule *rule = (Rule*)malloc(sizeof(Rule));
    if (rule == NULL)
        return NULL;

    rule->color = color;
    rule->contain = NULL;
    return rule;
}

int addRuleToList(Rule **rules, Rule *rule) {
    if (*rules == NULL) {
        *rules = rule;
        rule->next = NULL;
    }
    else {
        rule->next = *rules;
        *rules = rule;
    }
    return 0;
}

Child *createNewChild(char *color, int amount) {
    Child *child = (Child*)malloc(sizeof(Child));
    if (child == NULL)
        return NULL;

    child->amount = amount;
    child->color = color;

    return child;
}

int addChildToRule(Rule *rule, Child *child) {
    if (rule->contain == NULL) {
        rule->contain = child;
        rule->contain->next = NULL;
    } else {
        child->next = rule->contain;
        rule->contain = child;
    }

    return 0;
}

size_t printRuleContainer(Rule *rule) {
    Child *ptr = rule->contain;
    size_t length = 0;
    while (ptr != NULL) {
        printf("%d of %s\n", ptr->amount, ptr->color);
        ptr = ptr->next;
        length++;
    }
    return length;
}

size_t lengthListOfRules(Rule *rules) {
    Rule *ptr = rules;
    size_t length = 0;
    while (ptr != NULL){
        ptr = ptr->next;
        length++;
    }
    return length;
}

void printListOfRules(Rule *rules) {
    Rule *ptr = rules;
    while (ptr != NULL) {
        printf(">>%s\n", ptr->color);
        int container = printRuleContainer(ptr);
        if (container == 0)
            printf("contain no bags\n");
        ptr = ptr->next;
    }
}

// given a rules and color for matching
// return the name of rules of colors that have almost one of that color
void findContainers(Rule *rules, char *color, Container **container) {

    for (Rule *rl_ptr = rules; rl_ptr != NULL; rl_ptr = rl_ptr->next) {
        Child *chld_ptr = rl_ptr->contain;
        if (chld_ptr != NULL) { // avoid rules of bags thats doesnt have any bag color
            for (; chld_ptr != NULL; chld_ptr = chld_ptr->next) {
                if (strcmp(chld_ptr->color, color) == 0) { // !match


                    if (container == NULL) {
                        Container *container = (Container*) malloc(sizeof(Container));
                        container->color = chld_ptr->color;
                        container->amount = chld_ptr->amount;
                        container->rule = rl_ptr->color;
                        container->next = NULL;
                    } else {
                        Container *new = (Container*) malloc(sizeof(Container));
                        new->color = chld_ptr->color;
                        new->amount = chld_ptr->amount;
                        new->rule = rl_ptr->color;
                        new->next = *container;
                        *container = new;
                    }
                }
            }
        }
    }
}

void countBags(Rule *rules, char *color, Visited **visited) {
    int found = 0;

    if (*visited == NULL) {
        Visited *new = (Visited*) malloc(sizeof(Visited));
        new->color = color;
        new->next = *visited;
        *visited = new;
        found = 1;
    } else {
        for (Visited *vptr = *visited; vptr != NULL; vptr = vptr->next) {
            if (strcmp(vptr->color, color) == 0) {
                found++;
            }
        }
    }

    if (found == 0) {
        Visited *new = (Visited*) malloc(sizeof(Visited));
        new->color = color;
        new->next = *visited;
        *visited = new;
    }

    // That's so important! reset container for every iteration!
    Container *container = NULL;
    findContainers(rules, color, &container);

    // Recursion is coming!
    for (Container *ptr = container; ptr != NULL; ptr = ptr->next) {
        countBags(rules, ptr->rule, visited);
    }
}

Rule *lineToRule(char *line) {
    Rule *rule = NULL;
    Child *child = NULL;

    // Guess there's another smart way to do next
    // remove carriage return or new line
    strtok(line, "\r");
    strtok(line, "\n");

    // split input line by delimiter "contain "
    // in two strings: bag color and container
    char *delimiter = "contain ";
    char *contain = (char*) malloc(sizeof(char) * strlen(line));
    contain = strstr(line, delimiter);
    contain += strlen(delimiter);
    contain[strlen(contain) - 1] = '\0';

    size_t len = strlen(line) - strlen(contain) - strlen(delimiter) - 1; // minus one for extra space
    char *bag = (char*) malloc(sizeof(char) * len);
    strncpy(bag, line, len);
    bag[len] = '\0';

    // trim bag word from rule and container
    strremove(bag, " bags");
    strremove(bag, " bag");
    strremove(contain, " bags");
    strremove(contain, " bag");

    rule = createNewRule(bag);

    char *color = (char*) malloc(sizeof(char) * 128);
    while ((color = strsplit(&contain, ",")) != NULL) {
        if (color[0] == ' ') color++;

        if (strcmp(color, "no other") == 0) {
            rule->contain = NULL;
            return rule;
        } else {

            // get amount of bags
            // this is a weird manner of extract that number
            // but...
            len = strlen(color) - strlen(strstr(color, " "));
            char *number = malloc(sizeof(char) * 3);
            strncpy(number, color, len);
            number[len] = '\0';
            int amount = atoi(number);
            // ... is what I actually know how to do that shit!
            color += strlen(number) + 1;
            len = strlen(color) - strlen(number) + 1;
            char *childname = malloc(sizeof(char) * len);
            strncpy(childname, color, len);
            childname[len] = '\0';
            child = createNewChild(childname, amount);
            addChildToRule(rule, child);
        }
    }
    return rule;
}

void createRulesFromFile(Rule **rules, char *filepath) {
    FILE *fp = fopen(filepath, "r");

    if (fp == NULL) {
        perror("Failed: ");
        exit(0);
    }

    char lines[MAXSIZELINES];
    while (fgets(lines, sizeof(lines), fp) != NULL) {
        Rule *rule = lineToRule(lines);
        addRuleToList(rules, rule);
    }

    fclose(fp);
}

int solveFilePartOne(char *filepath) {
    Rule *rules = NULL;
    createRulesFromFile(&rules, filepath);

    /* printListOfRules(rules); */
    printf("Length of rules: %lld\n", lengthListOfRules(rules));

    Visited *visited = NULL;
    countBags(rules, "shiny gold", &visited);

    // count visited colors
    int len = 0;
    for (Visited *ptr = visited; ptr != NULL; ptr = ptr->next) {
        len++;
    }

    return len - 1; // minus one because input color
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        printf("Input puzzle: %s\n", argv[i]);
        int partOne = solveFilePartOne(argv[i]);
        printf("Part one solution: %d\n", partOne);

    }
    return 0;
}
