// A simple string processing library
// Taken lot of ideas and code from
// "Game Scripting Mastery" book

#include <string.h>
#include <stdint.h>

int is_char_numeric(char c) {
    return  c >= '0' && c <= '9' ? 1 : 0;
}

int is_char_whitespace(char c) {
    return c == ' ' || c == '\t' ? 1 : 0;
}

int is_char_variable(char c) {
    return c >= 'a' && c <= 'z' ? 1: 0;
}

int is_char_delimiter(char c) {
    return c == '[' || c == ']' ? 1 : 0;
}

int is_char_equal(char c) {
    return c == '=' ? 1 : 0;
}

int is_char_mask(char c) {
    return c == 'X' || c == '0' || c == '1' ? 1 : 0;
}

int is_string_mask(char *string) {
    if (string == NULL)
        return 0;

    if (strlen(string) == 0)
        return 0;

    for (uint8_t current_char_index = 0;
         current_char_index < strlen(string);
         ++current_char_index) {
        if (!is_char_mask(string[current_char_index]))
            return 0;
    }

    return 1;
}


int is_string_integer(char *string) {
    if (string == NULL)
        return 0;

    if (strlen(string) == 0)
        return 0;

    for (uint8_t current_char_index = 0;
         current_char_index < strlen(string);
         ++current_char_index) {
        if (!is_char_numeric(string[current_char_index]))
            return 0;
    }

    return 1;
}

int is_string_whitespace(char *string) {
    if (string == NULL)
        return 0;

    if (strlen(string) == 0)
        return 0;

    for (uint8_t current_char_index = 0;
         current_char_index < strlen(string);
         ++current_char_index) {
        if (!is_char_whitespace(string[current_char_index]))
            return 0;
    }

    return 1;
}

int is_string_variable(char *string) {
    if (string == NULL)
        return 0;

    if (strlen(string) == 0)
        return 0;

    if (is_char_numeric(string[0]))
        return 0;

    for (uint8_t current_char_index = 0;
         current_char_index < strlen(string);
         ++current_char_index) {
        if (!is_char_variable(string[current_char_index]))
            return 0;
    }

    return 1;
}
