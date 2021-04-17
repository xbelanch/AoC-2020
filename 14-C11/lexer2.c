// Part 1: Introduction to Lexical Scanning
// From: https://github.com/DoctorWkt/acwj/blob/master/01_Scanner/Readme.md

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int token;
    int ivalue;
} Token;

typedef enum {
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_INTEGER_LITERAL,
} Tokens;

int Line;
int PutBack;
FILE *inputFile;

// Get the next character from the input file
static int nextCharacter(void) {
    int c;

    if (PutBack) {
        c = PutBack;
        PutBack = 0;
        return c;
    }

    c = fgetc(inputFile);
    if ('\n' == c)
        Line++;
    return c;
}

static int skipWhitespace(void) {
    int c;
    c = nextCharacter();
    while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
        c = nextCharacter();
    }
    return c;
}

static int isDigit(char c) {
    return c >= '0' && c <= '9' ? 1 :  0;
}

static int scanInt(char c) {
    int k, val = 0;
    while (isDigit(c)) {
        k = c - '0'; // convert char digit to integer
        val = val * 10 + k;
        c = nextCharacter(); // read next character
    }

    // We hit a non-integer character, so put it back
    PutBack = c;
    return val;
}


static int scanTokens(Token *t) {
    int c;

    // Skip whitespace, tabs and return carriages
    c = skipWhitespace();

    // Determine the token based on input character
    switch(c) {
    case EOF:
        return (0);
    case '+':
        t->token = TOKEN_PLUS;
        break;
    case '-':
        t->token = TOKEN_MINUS;
        break;
    case '*':
        t->token = TOKEN_STAR;
        break;
    case '/':
        t->token = TOKEN_SLASH;
        break;
    default:
        if (isDigit(c)) {
            t->ivalue = scanInt(c);
            t->token = TOKEN_INTEGER_LITERAL;
            break;
        }
        printf("Unknown character %c on line %d\n", c, Line);
        return (1);
    }
}

char *tokenstr[] = { "+", "-", "*", "/", "integer literal" };

void scanfile() {
    Token t = {0};
    while (scanTokens(&t)) {
        printf("Token %s", tokenstr[t.token]);
        if (t.token == TOKEN_INTEGER_LITERAL) {
            printf(", value %d", t.ivalue);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    char *file = argv[1];
    inputFile = fopen(file, "r");
    if (inputFile == NULL) {
        fprintf(stderr, "ERROR: Cannot open input file %s\n", inputFile);
    }

    scanfile();

    return 0;
}
