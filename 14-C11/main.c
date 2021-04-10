#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "string_processing.h"

#define MAX_SIZE_LINES 2048
#define MAX_SIZE_CHARACTERS 512

int todo(){
    printf("TODO:\n");
    return 0;
}

int tokenizer(char **lines) {
    (void)lines[0];
    return 0;
}

int test_string_processing() {
    assert(is_string_integer("000000000111001101"));
    // assert(is_string_whitespace("        a  ab "));
    assert(is_string_whitespace("            "));
    // assert(is_string_integer("729719379a228"));
    assert(is_string_variable("mem"));
    assert(is_string_variable("mask"));
    return 0;
}


int solve_file(char *filepath) {
    printf("%s\n", filepath);
    FILE *fp = fopen(filepath, "r");
    char chr;
    char buffer[MAX_SIZE_CHARACTERS];
    char lines[MAX_SIZE_LINES][MAX_SIZE_CHARACTERS];
    char *ptr = buffer;
    int num = 0;

    // read and store the input file
    while (1) {
        chr = fgetc(fp);
        if (feof(fp))
            break;
        if (chr == '\n') {
            *ptr = '\0';
            strcpy(lines[num++], buffer);
            ptr = buffer;

        } else {
            *ptr++ = chr;
        }
    }

    // print to stdout
    for (int i = 0; i < num; i++) {
        fprintf(stdout, "line[%d]: %s\n", i, lines[i]);
    }

    fclose(fp);
    return 0;
}

int dummy_parse_line(char *line) {
    if (line == NULL)
        return 0;
    if (strlen(line) == 0)
        return 0;

    int start_char_index = 0;
    int variable_found = 0;
    int number_value_found = 0;
    int found_some_value = 0;
    char *variable;
    char *number;
    char buffer[128];
    for (uint8_t end_char_index = 0; end_char_index < strlen(line); ++end_char_index) {

        buffer[end_char_index - start_char_index] = line[end_char_index];

        if (is_char_variable(line[end_char_index])) {
            variable_found = 1;
        }

        // Get variable 'mem' and memory address
        if (is_char_delimiter(line[end_char_index])) {
            if (variable_found) {
                buffer[end_char_index] = '\0';
                variable = malloc(sizeof(char) * (end_char_index - start_char_index));
                strcpy(variable, buffer);

                buffer[0] = 0;
                printf("variable: %s\n", variable);

                variable_found = 0;
            }

            if (line[end_char_index] == '[' && is_char_numeric(line[end_char_index + 1])) {
                number_value_found = 1;
                start_char_index = end_char_index + 1;
            }

            if (line[end_char_index] == ']' && number_value_found) {
                buffer[end_char_index - start_char_index] = '\0';
                number = malloc(sizeof(char) * (end_char_index - start_char_index));
                strcpy(number, buffer);
                buffer[0] = 0;
                printf("value: %s\n", number);
                number_value_found = 0;
            }
        } else { // @TODO: get mask

        }

        // Get value number
        if (is_char_equal(line[end_char_index]) &&
            is_char_numeric(line[end_char_index + 2])) {
            end_char_index += 1;
            start_char_index = end_char_index + 1;
            found_some_value = 1;
            buffer[0] = '\0';
        }

        if (found_some_value && line[end_char_index] == '\n') {
            buffer[end_char_index - start_char_index] = '\0';
            number = malloc(sizeof(char) * (end_char_index - start_char_index));
            strcpy(number, buffer);
            buffer[0] = '\0';
            printf("equal: %s\n", number);
            found_some_value = 0;
        }
    }

    return 1;
}


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv[0];
    // for (int i = 1; i < argc; i++) {
    //     solve_file(argv[i]);
    // }

    test_string_processing();
    dummy_parse_line("mem[8] = 11\n");
    dummy_parse_line("mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X\n");
    return 0;
}
