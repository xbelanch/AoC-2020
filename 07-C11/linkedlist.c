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

Rule *createNewRule(char *color) {
    Rule *rule = (Rule*)malloc(sizeof(Rule));
    if (rule == NULL)
        return NULL;

    rule->color = color;
    rule->contain = NULL;
    return rule;
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

size_t printRuleContainer(Rule *rule) {
    Child *child = rule->contain;
    size_t length;
    while (child != NULL) {
        printf("%d of %s\n", child->amount, child->color);
        child = child->next;
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

void testingLinkedList() {
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
    child = createNewChild("shiny bag", 1);
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

    printListOfRules(rules);

    printf("Length of rules: %lld", lengthListOfRules(rules));

}




int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        printf("Input puzzle: %s\n", argv[i]);
    }

    testingLinkedList();
    return 0;
}
