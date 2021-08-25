#ifndef HELPER_H
#define HELPER_H

#define MAX_SIZE_LINES 16384

typedef struct {
    char **lines;
    size_t size;
} InputTextFile;

int isDigit(char c) {
    return (c >= '0' && c <= '9') ? (1) : (0);
}

int isSymbol(char c, char symbol) {
    return (c == symbol) ? (1) : (0);
}

int isSpace(char c) {
    return (c == 32) ? (1) : (0);
}

int isNewLine(char c) {
    return (c == '\n') ? (1) : (0);
}

int isCharacter(char c) {
    return (c >= 'a' && c <= 'z') ? (1) : (0);
}

int getLines(FILE *fp, InputTextFile *inputTextFile) {

    if (fp == NULL || inputTextFile == NULL)
        return(1);

    int c = 0;
    int last = 0;
    inputTextFile->lines = (char**)malloc(sizeof(char) * MAX_SIZE_LINES * MAX_SIZE_LINES);
    inputTextFile->size = 0;

    // Initialize first line
    inputTextFile->lines[0]  = (char*)malloc(sizeof(char) * MAX_SIZE_LINES);
    char *ptr = inputTextFile->lines[0];

    while((c = getc(fp)) != EOF) {
        if (isNewLine(c) && !isNewLine(last)) {
            inputTextFile->size++;
            inputTextFile->lines[inputTextFile->size] = (char*)malloc(sizeof(char) * MAX_SIZE_LINES);
            ptr = inputTextFile->lines[inputTextFile->size];
        } else {
            if (!(isNewLine(last) && isNewLine(c))) {
                *ptr = c;
                ptr++;
            }
        }
        last = c;
    }

    return(0);
}



#endif
