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
    int count;
    Child children[MAXCHILDRENSIZE];
} Rule;

// grabbed from: https://stackoverflow.com/questions/47116974/remove-a-substring-from-a-string-in-c
char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

// grabbed from: https://stackoverflow.com/questions/8512958/is-there-a-windows-variant-of-strsep-function
char* strsplit(char** stringp, const char* delim)
{
    char* start = *stringp;
    char* p;

    p = (start != NULL) ? strpbrk(start, delim) : NULL;

    if (p == NULL)
        {
            *stringp = NULL;
        }
    else
        {
            *p = '\0';
            *stringp = p + 1;
        }

    return start;
}

Rule lineToRule(char *line) {
    size_t len = 0;

    // split input line by delimiter "contain "
    // in two strings: rule and container
    char *delimiter = "contain ";
    char *pch = strstr(line, delimiter);
    pch += strlen(delimiter);

    // get container
    char *container = malloc(sizeof(char) * strlen(pch) + 1);
    strncpy(container, pch, strlen(pch));
    container[strlen(container) - 1] = '\0'; // remove last dot

    // get rule
    char *rulename = malloc(sizeof(char) * strlen(line) + 1);
    len = strlen(line) - strlen(pch) - strlen(delimiter);
    strncpy(rulename, line, len);
    rulename[len - 1] = '\0'; // remove last space

    // trim bag word from rule and container
    strremove(rulename, " bags");
    strremove(rulename, " bag");
    strremove(container, " bags");
    strremove(container, " bag");

    // split container in several entries or bags
    Rule rule;
    rule.name = rulename;
    char *bag;
    int count = 0;
    while ((bag = strsplit(&container, ",")) != NULL) {
        if (bag[0] == ' ') {
            bag++;
        }

        if (strcmp(bag, "no other") == 0) {
            printf("No bags found\n");
            rule.count = 0;
            break;
        } else {
            // get amount of bags
            len = strlen(bag) - strlen(strstr(bag, " "));
            char *number = malloc(sizeof(char) * strlen(bag) + 1);
            strncpy(number, bag, len);
            number[len] = '\0';
            int amount = atoi(number);

            // get name of bags
            char *pstr = strstr(bag, " ");
            pstr++;

            // store to child
            rule.children[count].amount = amount;
            rule.children[count].name = pstr;
        }
        count++;
    }

    // Store how many contain
    rule.count = count;

    return rule;
}

void printRule(Rule rule) {
    printf("Rule> %s:\n", rule.name);
    for (int i = 0; i < rule.count; i++) {
        printf("  %d of %s\n", rule.children[i].amount, rule.children[i].name);
    }

}


void solveFile(char *filepath) {
    printf("%s\n", filepath);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solveFile(argv[i]);
    }

    Rule rule = lineToRule("shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.");
    printRule(rule);

    return 0;
}
