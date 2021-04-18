// Part 1: Introduction to Lexical Scanning
// From: https://github.com/DoctorWkt/acwj/blob/master/01_Scanner/Readme.md

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Lexer stuff starts here --------------------

// Globals
int Line;
int PutBack;
FILE *inputFile;

typedef struct {
    int token;
    int ivalue;
} Token;

// need a global variable for handling the most recent token scanned
Token gToken;

typedef enum {
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_INTEGER_LITERAL,
    TOKEN_EOF
} Tokens;


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
        t->token = TOKEN_EOF;
        break;
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


// END of lexer stuff ------------------


// AST Stuff ----------------------------
// --------------------------------------

// AST node types
typedef enum {
    AST_ADD,
    AST_SUBSTRACT,
    AST_MULTIPLY,
    AST_DIVIDE,
    AST_INTEGER_LITERAL
} Nodes;

// Abstract Syntax Tree structure
typedef struct _astnode {
    int operation;
    struct _astnode *left;
    struct _astnode *right;
    int intValue;
} ASTnode;

// Make brand new generic and return AST node
ASTnode *newASTnode(int operation,
                    ASTnode *left,
                    ASTnode *right,
                    int intValue) {
    ASTnode *node;
    node = (ASTnode*) malloc(sizeof(ASTnode));

    if (node == NULL) {
        fprintf(stderr, "Unable to malloc in newASTnode()\n");
        exit(1);
    }

    // Copy field values and return it
    node->operation = operation;
    node->left = left;
    node->right = right;
    node->intValue = intValue;
    return (node);
}

// Make AST leaf node: no childs
ASTnode *newASTleafnode(int operation, int intValue) {
    return newASTnode(operation, NULL, NULL, intValue);
}

// Make unary AST node: only one child
ASTnode *newASTunarynode(int operation, ASTnode *left, int intValue) {
    return newASTnode(operation, left, NULL, intValue);
}


// A first navie implementation expression parser
// Convert a token into an AST
Nodes arithmetic_operations(Tokens t){
    switch(t) {
    case TOKEN_PLUS:
        return (AST_ADD);
    case TOKEN_MINUS:
        return (AST_SUBSTRACT);
    case TOKEN_STAR:
        return (AST_MULTIPLY);
    case TOKEN_SLASH:
        return (AST_DIVIDE);
    default:
        fprintf(stderr, "Unknown token in arithmetic_operation() on line %d\n", Line);
        exit(1);
    }
}

// We need a function to check that the next token in an integer literal:

ASTnode *primary(void) {
    ASTnode *node;

    // For an Integer Literal token, make a leaf AST node for it
    // and scan in the next token. Otherwise, a syntax error
    // for any other token type
    switch (gToken.token) {
    case TOKEN_INTEGER_LITERAL:
        node = newASTleafnode(AST_INTEGER_LITERAL, gToken.ivalue);
        scanTokens(&gToken);
        return (node);
    default:
        fprintf(stderr, "Syntax error on line %d\n", Line);
        exit(1);
    }
}


ASTnode *binExpression(void) {
    ASTnode *node, *left, *right;
    Nodes nodeType;

    // Get the integer literal on the left
    // Fetch next token at the same time
    left = primary();

    // no tokens left, return just the left node
    if (gToken.token == TOKEN_EOF)
        return (left);

    // Convert the token into a node type
    nodeType = arithmetic_operations(gToken.token);

    // Get the next token in
    scanTokens(&gToken);

    // Recursively get the right-hand tree
    right = binExpression();

    // Now build a tree with both sub-trees
    node = newASTnode(nodeType, left, right, 0);
    return (node);
}

// What the neck is telling me the parser
// Given an AST node, interpret the operators in it
// and return a final value

int interpretAST(ASTnode *node) {
    int leftval, rightval;

    // Get the left and right subtrees values
    if (node->left)
        leftval = interpretAST(node->left);

    if (node->right)
        rightval = interpretAST(node->right);

    switch(node->operation) {
    case AST_ADD:
        printf("%d + %d\n", leftval, rightval);
        return (leftval + rightval);
    case AST_SUBSTRACT:
        printf("%d - %d\n", leftval, rightval);
        return (leftval - rightval);
    case AST_MULTIPLY:
        printf("%d * %d\n", leftval, rightval);
        return (leftval * rightval);
    case AST_DIVIDE:
        printf("%d / %d\n", leftval, rightval);
        return (leftval / rightval);
    case AST_INTEGER_LITERAL:
        return (node->intValue);
    default:
        fprintf(stderr, "Unknown AST operator %d\n", node->operation);
        exit(1);
    }

    return (0);
}


// end of AST nodes stuff -----------------------------

void scanfile() {
    gToken = (Token){0};
    scanTokens(&gToken); // take firs token
    ASTnode *node = binExpression();
    printf("Result: %d\n", interpretAST(node));


    // while (scanTokens(&t)) {
    // printf("Token %s", tokenstr[t.token]);
    //     if (t.token == TOKEN_INTEGER_LITERAL) {
    //         printf(", value %d", t.ivalue);
    //     }
    //     printf("\n");
    // }
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
