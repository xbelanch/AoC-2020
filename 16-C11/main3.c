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
size_t nearbyTickets[1024][1024];
size_t sz_nearbyTickets;
size_t myTicket[32];
size_t sz_myTicket;

bool in_range(size_t min, size_t max, size_t val) {
    return val - min <= max - min ? true : false;
}

int log_data() {
    // Ranges
    for (size_t i = 0; i < sz_ranges; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            fprintf(stdout, "%lu ", ranges[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');

    // Your Ticket
    for (size_t i = 0; i < sz_myTicket; ++i) {
        fprintf(stdout, "%lu,", myTicket[i]);
    }
    putchar('\n');
    putchar('\n');

    // Nearby Tickets
    for (size_t i = 0; i < sz_nearbyTickets; ++i) {
        for (size_t j = 0; nearbyTickets[i][j] < (size_t)-1; ++j) {
            fprintf(stdout, "%lu,", nearbyTickets[i][j]);
        }
        putchar('\n');
    }

    return(0);
}

int get_data() {
    char *num = (char*)(malloc(sizeof(char) * 8));
    char last;
    size_t j = 0;
    size_t k = 0;
    size_t column = 0;
    bool yticket = false;
    bool ntickets = false;

    for (size_t i = 0; i < sz_lines; ++i) {
        if (strcmp("your ticket:\n", lines[i]) == 0)
            yticket = true;

        if (strcmp("nearby tickets:\n", lines[i]) == 0)
            ntickets = true;

        // get and save ranges
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
        if (yticket && isDigit(lines[i][0])) {
            for (char *p = lines[i]; *p != '\0'; ++p) {
                if (isDigit(*p)) {
                    num[j++] = *p;
                } else if (*p == ',' || *p == '\n') {
                    num[j] = '\0';
                    myTicket[sz_myTicket++] = atoll(num);
                    j = 0;
                }
            }
            yticket = false;
        }

        if (ntickets && isDigit(lines[i][0])) {
            for (char *p = lines[i]; *p != '\0'; ++p) {
                if (isDigit(*p)) {
                    num[j++] = *p;
                } else if (*p == ',') {
                    num[j] = '\0';
                    nearbyTickets[sz_nearbyTickets][column++] = atoll(num);
                    j = 0;
                } else if (*p == '\n') {
                    num[j] = '\0';
                    nearbyTickets[sz_nearbyTickets++][column] = atoll(num);
                    j = 0;
                    column = 0;
                }
            }
        }
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




size_t solutionPartOne() {
    size_t solution = 0;
    size_t match = 0;
    size_t value = 0;
    for (size_t i = 0; i < sz_nearbyTickets; ++i) {
        for (size_t j = 0; nearbyTickets[i][j] < (size_t)-1; ++j) {
            value = nearbyTickets[i][j];
            for (size_t k = 0; k < sz_ranges; ++k) {
                if (in_range(ranges[k][0], ranges[k][1], value) ||
                    in_range(ranges[k][2], ranges[k][3], value)) {
                    break;
                } else {
                    match++;
                }
            }

            if (match == sz_ranges) {
                // fprintf(stdout, "!%lu! at %lu\n", value, i);
                solution += value;

                // Discard all invalid nearby tickets
                for (size_t r = i; r < sz_nearbyTickets; ++r) {
                    for (size_t s = 0; nearbyTickets[r][s] < (size_t)-1; ++s) {
                        nearbyTickets[r][s] = nearbyTickets[r + 1][s];
                    }
                }
                sz_nearbyTickets--;
                // fix bug when invalid values belongs to first nearby ticket of the list
                if (i != 0)
                    i--;
            }

            if (match > 0) {
                match = 0;
            }

        }
    }

    return(solution);
}

size_t solutionPartTwo() {
    size_t solution = 0;

    return(solution);
}


int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    // initialize nearby tickets
    for (size_t i = 0; i < 1024; ++i) {
        for (size_t j = 0; j < 1024; ++j) {
            nearbyTickets[i][j] = (size_t)-1;
        }
    }

    char *filename = "input.txt";
    parse_input_file(filename);
    get_data();

    /*
     * Tsoding Solution:
     * Part 1: 23925
     * Part 2: 964373157673
     */

    fprintf(stdout, "Solution for part One: %lu\n", solutionPartOne());
    // log_data();

    return(0);
}
