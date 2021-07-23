#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "./hashmap.c/hashmap.h"
#include "jelp.h"

Line *lines;

int address_compare(const void *a, const void *b, void *udata) {
    const Memory *_a = a;
    const Memory *_b = b;
    return _a->addr > _b->addr ? 1 : 0;
}

size_t memory_hash(const void *item, uint64_t seed0, uint64_t seed1) {
    return 0;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    char *sample_file = "sample-01.txt";
    FILE *input_file = fopen(sample_file, "rb");
    if (NULL == input_file) {
        fprintf(stderr, "ERROR: File \033[0;31m%s\033[0m not found.\n", sample_file);
        exit(0);
    }

    lines = malloc(sizeof(Line) * MAX_SIZE_LINES);
    size_t j = 0; size_t i = 0;
    char *string = malloc(sizeof(char) * MAX_SIZE_LINE);
    int c = fgetc(input_file);
    while (EOF != c) {
        string[i++] = c;
        if ('\n' == c) {
            string[i-1] = '\0';
            lines[j].string = malloc(sizeof(char) * (i-1));
            memcpy(lines[j].string, string, i-1);
            lines[j].n = j;
            j++; i = 0;
            string[i] = '\0';
        }
        c = fgetc(input_file);
    }
    lines[j].string = NULL;
    lines[j].n = -1;

    i = 0;
    while (lines[i].string) {

        i++;
    }

    fclose(input_file);

    struct hashmap *map = hashmap_new(sizeof(Memory), 0, 0, 0, memory_hash, address_compare, NULL);

    //    hashmap_set(map, &(Memory){ .addr = (1UL << 35), .value = 25 });
    hashmap_set(map, &(Memory){ .addr = 198299, .value = 10 });
    hashmap_set(map, &(Memory){ .addr = 22927282, .value = 15 });
    hashmap_set(map, &(Memory){ .addr = 1UL << 35 + 1, .value = 20 });

    Memory *mem;
    mem = hashmap_get(map, &(Memory){ .addr = 1UL << 35 + 1});
    printf("Memory value: %lu at addr: %lu\n", mem->value, mem->addr);
    mem->value = 32003;
    printf("Memory value: %lu at addr: %lu\n", mem->value, mem->addr);

    hashmap_free(map);
    return 0;
}
