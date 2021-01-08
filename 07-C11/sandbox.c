#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yastring.h"

typedef struct child {
    char *color;
    int amount;
    struct child *next;
    struct rule *rule;
} Child;

typedef struct rule {
    char *color;
    struct child *contain;
    struct rule *next;
} Rule;

typedef struct visited {
    char *color;
    struct visited *next;
} Visited;

typedef struct list {
    char *color;
    struct list *next;
} List;

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
    child->rule = NULL;

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

    child->rule = rule;

    return 0;
}


size_t printRuleContainer(Rule *rule) {
    Child *ptr = rule->contain;
    size_t length;
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
        printf("%s\n", ptr->color);
        int container = printRuleContainer(ptr);
        if (container == 0)
            printf("contain no bags\n");
        ptr = ptr->next;
    }
}

int isVisited(Visited *visited, char *color) {
    for (Visited *ptr = visited; ptr != NULL; ptr = ptr->next) {
        printf("%s : %s\n", ptr->color, color);
        if (strcmp(ptr->color, color) == 0) {
            printf("Match!\n");
            return 1;
        }
    }
    return 0;
}

void printVisitedList(Visited *visited) {
    printf("Visited colors: ");
    for (Visited *v = visited; v != NULL; v = v->next) {
        printf("%s ", v->color);
    }
    printf("\n");
}

int lengthVisitedList(Visited *visited) {
    Visited *ptr = visited;
    int length = 0;
    while (ptr != NULL) {
        ptr = ptr->next;
        length++;
    }
    return length;
}

// given a rules and color for matching
// return the name of rules of colors that have almost one of that color
void findContainers(Rule *rules, char *color, char **result) {

    for (Rule *rl_ptr = rules; rl_ptr != NULL; rl_ptr = rl_ptr->next) {
        Child *chld_ptr = rl_ptr->contain;
        if (chld_ptr != NULL) { // avoid rules of bags thats doesnt have any bag color
            for (; chld_ptr != NULL; chld_ptr = chld_ptr->next) {
                if (strcmp(chld_ptr->color, color) == 0) { // !match
                    *result = (char*) (malloc(sizeof(char) * strlen(color)));
                    *result = rl_ptr->color; // store the color rule bag that contain the that color
                    result++;
                    *result = NULL;
                    findContainers(rules, rl_ptr->color, result);
                    break;
                }
            }
        }
    }

}

int testingLinkedList() {
    Rule *rules = NULL; // Initialize list of rules
    Rule *rule = NULL;
    Child *child = NULL;

    rule = createNewRule("light red");
    child = createNewChild("bright white", 1);
    addChildToRule(rule, child);
    child = createNewChild("muted yellow", 2);
    addChildToRule(rule, child);
    addRuleToList(&rules, rule);

    rule = createNewRule("dark orange");
    child = createNewChild("bright white", 3);
    addChildToRule(rule, child);
    child = createNewChild("muted yellow", 4);
    addChildToRule(rule, child);
    addRuleToList(&rules, rule);

    rule = createNewRule("bright white");
    child = createNewChild("shiny gold", 1);
    addChildToRule(rule, child);
    addRuleToList(&rules, rule);

    rule = createNewRule("muted yellow");
    child = createNewChild("shiny gold", 2);
    addChildToRule(rule, child);
    child = createNewChild("faded blue", 9);
    addChildToRule(rule, child);
    addRuleToList(&rules, rule);

    rule = createNewRule("shiny gold");
    child = createNewChild("dark olive", 1);
    addChildToRule(rule, child);
    child = createNewChild("vibrant plum", 2);
    addChildToRule(rule, child);
    addRuleToList(&rules, rule);

    rule = createNewRule("dark olive");
    child = createNewChild("faded blue", 3);
    addChildToRule(rule, child);
    child = createNewChild("dotted black", 4);
    addChildToRule(rule, child);
    addRuleToList(&rules, rule);

    rule = createNewRule("vibrant plum");
    child = createNewChild("faded blue", 5);
    addChildToRule(rule, child);
    child = createNewChild("dotted black", 6);
    addChildToRule(rule, child);
    addRuleToList(&rules, rule);

    rule = createNewRule("faded blue");
    addRuleToList(&rules, rule);

    rule = createNewRule("dotted black");
    addRuleToList(&rules, rule);

    /* printListOfRules(rules); */
    printf("Length of rules: %lld\n", lengthListOfRules(rules));

    char **result = (char**) malloc(sizeof(char));
    char *color = "shiny gold"; // start color
    // Recursion...
    findContainers(rules, color, result);

    int solution = 0;
    for (char **color = result; *color != NULL; color++) {
        printf("%s, ", *color);
        solution++;
    }

    printf("len: %d\n", solution);
    return solution;
}




int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        printf("Input puzzle: %s\n", argv[i]);
    }

    testingLinkedList();
    return 0;
}
