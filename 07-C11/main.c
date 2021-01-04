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

void lineToRule(char *line) {
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
    char *rule = malloc(sizeof(char) * strlen(line) + 1);
    len = strlen(line) - strlen(pch) - strlen(delimiter);
    strncpy(rule, line, len);
    rule[len - 1] = '\0'; // remove last space

    // trim bag word from rule and container
    strremove(rule, " bags");
    strremove(rule, " bag");
    strremove(container, " bags");
    strremove(container, " bag");

    // split container in several entries or bags
    char *bags[32];
    char *bag;
    int i = 0;
    while ((bag = strsplit(&container, ",")) != NULL) {
        if (bag[0] == ' ') {
            bag++;
        }

        bags[i] = bag;

        if (strcmp(bags[i], "no other") == 0) {
            printf("No bags found\n");
        } else {
            // get amount of bags
            len = strlen(bags[i]) - strlen(strstr(bags[i], " "));
            char *number = malloc(sizeof(char) * strlen(bags[i] + 1));
            strncpy(number, bags[i], len);
            number[len] = '\0';
            int amount = atoi(number);
            printf("%d\n", amount);
        }
        bags[i + 1] = NULL;
        i++;
    }

    // print it to stdout
    printf("-%s-\n", rule);
    for (int i = 0; bags[i] != NULL; i++) {
        printf("-%s-\n", bags[i]);
    }
}

/* Rule lineToRule(char *line) { */
/*     Rule rule = { */
/*         "u pogger", */
/*         {{"mate", 1 }} */
/*     }; */
/*     return rule; */
/* } */

void solveFile(char *filepath) {
    printf("%s\n", filepath);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solveFile(argv[i]);
    }

    lineToRule("muted gold bags contain 1 wavy red bag, 3 mirrored violet bags, 5 bright gold bags, 5 plaid white bags.");
    return 0;
}
