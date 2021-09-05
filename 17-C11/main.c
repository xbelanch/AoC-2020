#include <stdio.h>
#include <stdlib.h>

int cycle = 0;
int last_state[3][3];
int new_state[3][3];
int z = 0;

void log_new_state() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            fprintf(stdout, "%c", new_state[row][col] == 1 ? '#' : '.');
        }
        putchar('\n');
    }
}

void rules(int row, int col) {
    int active_neighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int k, l;
            if (!(i == 0 && j == 0)) { // avoid check yoursel
                if ((k = row + i) < 0) {
                    k = k + 3;
                }

                if ((l = col + j) < 0) {
                    l = l + 3;
                }

                fprintf(stdout, "[%d][%d](%d) ", k, l, last_state[k][l]);
                if (last_state[k][l] == 1) active_neighbors++;
            } else {
                fprintf(stdout, "[0][0](%d)", last_state[k][l]);
            }
        }
        putchar('\n');
    }
    if (last_state[row][col] && !(active_neighbors == 2 || active_neighbors == 3))
        new_state[row][col] = 0;

    if (!last_state[row][col] && active_neighbors == 5)
        new_state[row][col] = 1;
}

void run() {
    for (int row = 0; row < 1; ++row) {
        for (int col = 0; col < 1; ++col) {
            rules(row, col);
        }
    }
    cycle++;
}



int parse_input(char *filename) {
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL)
        return (1);

    int chr;
    int row = 0, col = 0;
    while ((chr = getc(fp)) != EOF) {
        if (chr == '.')
            last_state[row][col++] = 0;

        if (chr == '#')
            last_state[row][col++] = 1;

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
    for (int i = -12; i < 12; ++i) {
        fprintf(stdout, "%d ", abs(i % 3));
    }
    // run();
    // log_new_state();

    return (0);
}
