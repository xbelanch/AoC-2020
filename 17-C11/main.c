#include <stdio.h>
#include <stdlib.h>

int state[3][3];

void log_state() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            fprintf(stdout, "%c", state[row][col] == 1 ? '@' : '-');
        }
        putchar('\n');
    }
}

int parse_input(char *filename) {
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL)
        return (1);

    int chr;
    int row = 0, col = 0;
    while ((chr = getc(fp)) != EOF) {
        if (chr == '.')
            state[row][col++] = 0;

        if (chr == '#')
            state[row][col++] = 1;

        if (chr == '\n') {
            col = 0;
            row++;
        }
    }
    fclose(fp);

    return (0);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    char *filename = "sample-input.txt";
    parse_input(filename);
    log_state();

    return (0);
}
