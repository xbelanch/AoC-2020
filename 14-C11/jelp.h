// jelp.h

#define MAX_SIZE_LINES 1024
#define MAX_SIZE_LINE 512
#define BITMASK_SIZE 35

typedef struct memory {
    size_t addr;
    size_t value;
} Memory;

typedef struct line {
    char *string;
    size_t n;
} Line;

// Stolen from https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
static int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

static char *bin(size_t value) {
    char *binary = malloc(sizeof(char) * BITMASK_SIZE);
    for (int i = BITMASK_SIZE; i >= 0; --i) {
        int k = value >> i;
        binary[BITMASK_SIZE - i] = k & 1 ? '1' : '0';
    }
    return binary;
}

static size_t bin2dec(char *value) {
    size_t decimal = 0;
    for (int i = BITMASK_SIZE; i >= 0; --i) {
        if (value[i] == '1') {
            decimal += 1UL << (BITMASK_SIZE - i);
        }
    }
    return decimal;
}

static char *bitmask_op(char* mask, char *value) {
    for (int i = BITMASK_SIZE; i >= 0; --i) {
        if (mask[BITMASK_SIZE - i] != 'X')
            value[BITMASK_SIZE - i] = mask[BITMASK_SIZE - i];
    }
    return value;
}

static int parse_input_file(Line *lines, size_t size) {
    for (int i = 0; i < size; ++i) {
        if (0 == strncmp(lines[i].string, "mem", 3)) {
            // Set mask to NULL
            // lines[i].mask = NULL;

            // // Extract memory address value
            // char *p_open_bracket = strchr(lines[i].text, '[');
            // char *p_close_bracket = strchr(lines[i].text, ']');
            // size_t diff = p_close_bracket - p_open_bracket;
            // char *mem = (char *)malloc(sizeof(char) * (diff - 1));
            // char *ptr = lines[i].text + 4; // mem[
            // memcpy(mem, ptr, diff - 1);
            // lines[i].addr = atoi(mem);

            // // Extract assigned memory value
            // char *p_equal = strchr(lines[i].text, '=');
            // diff = p_equal - lines[i].text;
            // size_t len = strlen(lines[i].text) - (diff + 2);
            // char *value = (char *)malloc(sizeof(char) * len);
            // ptr = lines[i].text + diff + 2;
            // memcpy(value, ptr, len);
            // lines[i].value = atoll(value);
        } else {
            // Extract mask value
            // size_t len = strlen(lines[i].text) - 7;
            // lines[i].mask = (char *)malloc(sizeof(char) * len);
            // char *ptr = lines[i].text + 7;
            // memcpy(lines[i].mask, ptr, len);
        }
    }
    fprintf(stdout, "Total number of lines: %d\n", size);
    return 0;
}
