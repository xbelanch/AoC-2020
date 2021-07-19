#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "./hashmap.c/hashmap.h"

typedef struct memory {
    size_t addr;
    size_t value;
} Memory;

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];
    struct hashmap *map = hashmap_new(sizeof(Memory), USHRT_MAX, 0, 0, NULL, NULL, NULL);
    hashmap_free(map);
    return 0;
}
