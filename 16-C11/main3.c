// This is a shame

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "helper.h"

char *lines[1024];
size_t sz_lines;
size_t ranges[32][4];
size_t sz_ranges;
size_t nearbyTickets[512][512];
size_t myTicket[32];


bool in_range(size_t min, size_t max, size_t val) {
    return val - min <= max - min ? true : false;
}

int log_lines() {
    for (size_t i = 0; i < sz_lines; ++i) {
        fprintf(stdout, "%s", lines[i]);
        putchar('\n');
    }
    return(0);
}

int get_ranges() {
    char *num = (char*)(malloc(sizeof(char) * 8));
    char last;
    size_t j = 0;
    size_t k = 0;
    sz_ranges = 0;
    for (size_t i = 0; i < sz_lines; ++i) {
        if (strchr(lines[i], '-') != NULL) {
            for (char *p = strchr(lines[i], ':'); *p != '\0'; ++p) {
                if (isDigit(*p)) {
                    num[j++] = *p;
                } else if ((*p == '-') ||
                           (*p == ' ' && isDigit(last))) {
                    num[j] = '\0';
                    ranges[sz_ranges][k++] = atoll(num);
                    j = 0;
                } else if (*p == '\n' && isDigit(last)) {
                    num[j] = '\0';
                    ranges[sz_ranges][k++] = atoll(num);
                    j = 0;
                    k = 0;
                    sz_ranges++;
                }
                last = *p;
            }
        }
    }

    for (size_t i = 0; i < sz_ranges; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            fprintf(stdout, "%lu ", ranges[i][j]);
        }
        putchar('\n');
    }

    return(0);
}


int parse_input_file(char *filename) {
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL) {
        fprintf(stdout, "ERROR: Input file %s not found!\n", filename);
        return(1);
    }
    int c;
    int i = 0;
    sz_lines = 0;
    lines[sz_lines] = (char*)malloc(sizeof(char) * 1024);
    while ((c = getc(fp)) != EOF) {
        if (c == '\n') {
            lines[sz_lines][i] = '\n';
            i = 0;
            sz_lines++;
            lines[sz_lines] = (char*)malloc(sizeof(char) * 1024);
        } else {
            lines[sz_lines][i++] = c;
        }
    }
    fclose(fp);
    return(0);
}


int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    char *filename = "sample-input.txt";
    parse_input_file(filename);
    // log_lines();
    get_ranges();

    return 0;
}
