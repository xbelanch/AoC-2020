// This is a shame

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "helper.h"

char *lines[1024];
size_t sz_lines;
char *fields[64];
size_t sz_fields;
size_t ranges[64][4];
size_t sz_ranges;
size_t nearbyTickets[1024][1024];
size_t sz_nearbyTickets;
size_t myTicket[32];
size_t sz_myTicket;

bool in_range(size_t min, size_t max, size_t val) {
    return val - min <= max - min ? true : false;
}

int log_data() {
    // Fields with its ranges
    for (size_t i = 0; i < sz_fields ; ++i) {
        fprintf(stdout, "%s ", fields[i]);
        for (size_t j = 0; j < 4; ++j) {
            fprintf(stdout, "%lu ", ranges[i][j]);
        }
        putchar('\n');
    }

    // Your Ticket
    fprintf(stdout, "my: ");
    for (size_t i = 0; i < sz_myTicket; ++i) {
        fprintf(stdout, "%lu,", myTicket[i]);
    }
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

        // get and save fields and ranges
        if (strchr(lines[i], '-') != NULL) {

            // get fields
            j = 0;
            fields[i] = (char*) malloc(sizeof(char) * 128);
            for (char *p = lines[i]; p != strchr(lines[i], ':'); ++p) {
                fields[i][j++] = *p;
            }
            fields[i][j] = '\0';
            sz_fields++;

            // get ranges for every field
            j = 0;
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

bool inRange(size_t field, size_t value) {
    return (in_range(ranges[field][0], ranges[field][1], value) ||
            in_range(ranges[field][2], ranges[field][3], value));
}

size_t solutionPartTwo() {

    size_t transpose[1024][1024];
    for (size_t i = 0; i < 1024; ++i) {
        for (size_t j = 0; j < 1024; ++j) {
            transpose[i][j] = (size_t)-1;
        }
    }

    // fucking matrix invers transpose
    for (size_t i = 0; i < sz_nearbyTickets; ++i) {
        for (size_t j = 0; nearbyTickets[i][j] < (size_t)-1; ++j) {
            transpose[j][i] = nearbyTickets[i][j];
        }
    }

    size_t max_columns = 0;
    for (size_t i = 0; transpose[0][i] < (size_t)-1; ++i) max_columns++;

    size_t max_rows = 0;
    for (size_t i = 0; transpose[i][0] < (size_t)-1; ++i) max_rows++;

    size_t match[max_rows];
    for (size_t i = 0; i < max_rows; ++i) match[i] = 0;

    size_t found[max_rows];
    for (size_t i = 0; i < max_rows; ++i) found[i] = 0;

    size_t result[max_rows][max_rows];
    for (size_t i = 0; i < max_rows; ++i)
        for (size_t j = 0; j < max_rows; ++j)
            result[i][j] = 0;


    size_t field;
    for (size_t i = 0; i < max_rows; ++i) {
        for (size_t j = 0; j < max_columns; ++j) {
            size_t value = transpose[i][j];
            for (field = 0; field < sz_ranges; ++field) {
                if (in_range(ranges[field][0], ranges[field][1], value) ||
                    in_range(ranges[field][2], ranges[field][3], value)) {
                    match[field]++;
                    // fprintf(stdout, "match: %lu at field: %lu\n", value, field);
                }
            }
        }

        for (size_t l = 0; l < sz_ranges; ++l) {
            // fprintf(stdout, "match[%lu] = %lu ", l, match[l]);
            if (match[l] == max_columns && !found[l]) {
                // putchar('<');
                result[i][l]++;
                found[l] = 0;
                // break;
            }
            // putchar('\n');
        }

        // reset
        for (size_t i = 0; i < max_rows; ++i) match[i] = 0;
    }

    // now we reorder the matrix depending on result or copy on a new matrix
    size_t matrix2[max_rows][max_rows];

    for (size_t i = 0; i < max_rows; ++i) {
        for (size_t j = 0; j < max_rows; ++j) {
            matrix2[i][j] = 0;
        }
    }

    // traverse raw result and sort the rows depending of number of matches
    // the goal is discard duplicated matches like the simple example of
    // part two
    // Save the index!
    size_t index[max_rows];
    size_t sum = 0;
    for (size_t i = 0; i < max_rows; ++i) {
        fprintf(stdout, "%lu: ", i);
        for (size_t j = 0; j < max_rows; ++j) {
            if (result[i][j])
                sum++;
            fprintf(stdout, "%lu,", result[i][j]);
        }
        index[sum - 1] = i;
        fprintf(stdout, ": (%lu matches)", sum);
        for (size_t k = 0; k < max_rows; ++k) {
            matrix2[sum - 1][k] = result[i][k];
        }
        putchar('\n');
        sum = 0;
    }

    // traverse  matrix2 and discard duplicated matches
    size_t found2[max_rows];
    for (size_t i = 0; i < max_rows; ++i) found2[i] = 0;

    for (size_t i = 0; i < max_rows; ++i) {
        for (size_t j = 0; j < max_rows; ++j) {
            if (matrix2[i][j] && !found2[j]) {
                found2[j] = 1;
            } else {
                matrix2[i][j] = 0;
            }
        }
    }
    putchar('\n');

    size_t whatColumn[max_rows];
    size_t fuck[6];
    size_t lenfuck = 0;
    size_t solution = 1;
    for (size_t i = 0; i < max_rows; ++i) {
        fprintf(stdout, "%lu: ", i);
        for (size_t j = 0; j < max_rows; ++j) {
            fprintf(stdout, "%lu,", matrix2[i][j]);
            if (matrix2[i][j])
                whatColumn[i] = j;
        }
        fprintf(stdout, " (%lu) -> (%lu)", whatColumn[i], index[i]);
        if ( whatColumn[i] < 6)
            fuck[lenfuck++] = index[i];
        putchar('\n');
    }

    // Okay guys... this is shit...
    for (size_t i = 0; i < lenfuck; ++i) {
        fprintf(stdout, "%lu ", fuck[i]);
        solution *= myTicket[fuck[i]];
    }

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

    // char *filename = "sample-input2.txt";
    // char *filename = "tsoding.txt";
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
    fprintf(stdout, "Solution for part Two: %lu\n", solutionPartTwo());

    return(0);
}
