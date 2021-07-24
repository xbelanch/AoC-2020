#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "./hashmap.c/hashmap.h"
#include "jelp.h"

Line *lines;
size_t result = 0;

int address_compare(const void *a, const void *b, void *udata) {
    (void) udata;
    const Memory *_a = a;
    const Memory *_b = b;
    return _a->addr < _b->addr ? 1 : 0;
}

size_t memory_hash(const void *item, uint64_t seed0, uint64_t seed1) {
    const Memory *memory = item;
    return hashmap_sip(memory, sizeof(memory), seed0, seed1);
}

bool sum(const void *item, void *udata) {
    (void) udata;
    const Memory *memory = item;
    // fprintf(stdout, "addr[%lu]: %lu\n", memory->addr, memory->value);
    result += memory->value;
    return true;
}

int perm_addr(struct hashmap *map, char *mask, size_t addr, size_t value) {
    // apply mask to addr and return new mask
    char *addr_b = bin(addr);
    for (int i = BITMASK_SIZE; i >= 0; --i)
        addr_b[BITMASK_SIZE - i] = mask[BITMASK_SIZE - i] != 'X' ? mask[BITMASK_SIZE - i] | addr_b[BITMASK_SIZE - i] : 'X';


    // Check how floating bits the mask we got
    int floating_bits_count = 0;
    for (int i = BITMASK_SIZE; i >= 0 ; --i) {
        if (addr_b[i] == 'X')
            floating_bits_count++;
    }

    // no floating bits?
    if (0 == floating_bits_count)
        return 0;

    // Set the max number of mask permutations
    int max_perms = 1 << floating_bits_count;
    // printf("max_perms: %d  for mem[%lu]\n", max_perms, addr);
    char *perms[max_perms];
    for (int i = 0; i < max_perms; ++i)
        perms[i] = malloc(sizeof(char) * BITMASK_SIZE);

    char *variations[max_perms];
    for (int i = 0; i < max_perms; ++i)
        variations[i] = bin(i);

    char *last = malloc(sizeof(char)* BITMASK_SIZE);
    last = addr_b;

    int idx = 0;
    for (int i = 0; i < max_perms; ++i) {
        for (int j = BITMASK_SIZE; j >= 0; --j) {
            if (last[j] == 'X') {
                perms[i][j] = variations[i][BITMASK_SIZE - idx];
                idx++;
            } else {
                perms[i][j] = addr_b[j];
            }
        }
        idx = 0;
    }

    for (int i = 0; i < max_perms; ++i) {
        // set value for
        hashmap_set(map, &(Memory){
                .addr =bin2dec(perms[i]),
                .value = value
                });

        // fprintf(stdout, "[%s] = %lu\n", perms[i], bin2dec(perms[i]));
    }

    return 0;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];

    struct hashmap *map = hashmap_new(sizeof(Memory), 0, 0, 0, memory_hash, address_compare, NULL);

    char *sample_file = "input.txt";
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
    char *mask;
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

#ifdef PART_TWO
            perm_addr(map, mask, addr, val);

#else


            // fprintf(stdout, "mem[%lu] = %lu\n", addr, val);
            // apply mask to value
            char *value_bitmasked = bitmask_op(mask, bin(val));
            hashmap_set(map, &(Memory){
                    .addr = addr,
                    .value = bin2dec(value_bitmasked)
                });
#endif
        } else {
            size_t len = strlen(lines[i].string) - 7;
            mask = (char *)malloc(sizeof(char) * len);
            char *ptr = lines[i].string + 7;
            memcpy(mask, ptr, len);
            // fprintf(stdout, "mask = %s\n", mask);

        }
        i++;
    }

    fclose(input_file);

    // Memory *mem;
    // Lets iterate over all memory addresses!
#ifdef PART_ONE
    if (hashmap_scan(map, sum, NULL))
        fprintf(stdout, "Solution part One: %lu\n", result);
#else
    if (hashmap_scan(map, sum, NULL))
        fprintf(stdout, "Solution part Two: %lu\n", result);
#endif
    hashmap_free(map);
    return 0;
}
