#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "./hashmap.c/hashmap.h"

typedef struct memory {
    size_t addr;
    size_t value;
} Memory;

int value_compare(const void *a, const void *b, void *udata) {
    return 0;
}

size_t memory_hash(const void *item, uint64_t seed0, uint64_t seed1) {
    return 0;
}


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];
    struct hashmap *map = hashmap_new(sizeof(Memory), 0, 0, 0, memory_hash, value_compare, NULL);

    hashmap_set(map, &(Memory){ .addr = 0, .value = 15 });

    Memory *mem;
    mem = hashmap_get(map, &(Memory){ .addr = 0});
    printf("Memory value: %lu at addr: %lu\n", mem->value, mem->addr);

    hashmap_free(map);
    return 0;
}
