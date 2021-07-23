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

    struct hashmap *map = hashmap_new(sizeof(Memory), 0, 0, 0, memory_hash, address_compare, NULL);

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
    size_t addr; size_t val;
    while (lines[i].string) {
        if (0 == strncmp(lines[i].string, "mem", 3)) {
            char *p_open_bracket = strchr(lines[i].string, '[');
            char *p_close_bracket = strchr(lines[i].string, ']');
            size_t diff = p_close_bracket - p_open_bracket;
            char *mem = (char *)malloc(sizeof(char) * (diff - 1));
            char *ptr = lines[i].string + 4; // mem[
            memcpy(mem, ptr, diff - 1);
            addr = atoll(mem);

            char *p_equal = strchr(lines[i].string, '=');
            diff = p_equal - lines[i].string;
            size_t len = strlen(lines[i].string) - (diff + 2);
            char *value = (char *)malloc(sizeof(char) * len);
            ptr = lines[i].string + diff + 2;
            memcpy(value, ptr, len);
            val = atoll(value);

            hashmap_set(map, &(Memory){ .addr = addr, .value = val });
        }
        i++;
    }

    fclose(input_file);

    Memory *mem;
    mem = hashmap_get(map, &(Memory){ .addr = 7});
    fprintf(stdout, "Memory value: %lu at addr: %lu\n", mem->value, mem->addr);
    mem = hashmap_get(map, &(Memory){ .addr = 8});
    fprintf(stdout, "Memory value: %lu at addr: %lu\n", mem->value, mem->addr);

    hashmap_free(map);
    return 0;
}
