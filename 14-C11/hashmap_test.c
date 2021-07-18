#include <stdio.h>
#include <stdlib.h>
#include "./hashmap.c/hashmap.h"

struct user {
    char *name;
    int age;
};

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];
    struct hashmap *map = hashmap_new(sizeof(struct user), 0, 0, 0, NULL, NULL, NULL);
    hashmap_free(map);
    return 0;
}
