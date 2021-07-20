#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "./hashmap.c/hashmap.h"

struct memory {
    size_t addr;
    size_t value;
};

int address_compare(const void *a, const void *b, void *udata) {
    const struct memory *memorya = a;
    const struct memory *memoryb = b;
    return memorya->addr > memoryb->addr ? 1 : 0;
}

size_t memory_hash(const void *item, uint64_t seed0, uint64_t seed1) {
    return 0;
}


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];
    struct hashmap *map = hashmap_new(sizeof(struct memory), 0, 0, 0, memory_hash, address_compare, NULL);

    //    hashmap_set(map, &(struct memory){ .addr = (1UL << 35), .value = 25 });
    hashmap_set(map, &(struct memory){ .addr = 198299, .value = 10 });
    hashmap_set(map, &(struct memory){ .addr = 22927282, .value = 15 });
    hashmap_set(map, &(struct memory){ .addr = 6787826627, .value = 20 });

    struct memory *mem;
    mem = hashmap_get(map, &(struct memory){ .addr = 198299});
    printf("Memory value: %lu at addr: %lu\n", mem->value, mem->addr);
    mem->value = 32003;
    printf("Memory value: %lu at addr: %lu\n", mem->value, mem->addr);

    hashmap_free(map);
    return 0;
}
