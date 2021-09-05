#include <stdio.h>
#include <stdlib.h>

size_t cycle = 0;


int origin = 5;
int offset = 1;
int cell[32][32][32]; // z, y, x

int parse_input(char *filename) {
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL)
        return (1);

    int chr;
    int x = 0, y = 0, z = origin;
    while ((chr = getc(fp)) != EOF) {
        if (chr == '.')
            cell[z][y][x++] = 0;
        if (chr == '#')
            cell[z][y][x++] = 1;
        if (chr == '\n') {
            x = 0;
            y++;
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

    // print
    for (int depth = origin - offset; depth <= origin + offset; ++depth) {
        fprintf(stdout, "z=%d\n", depth - origin);
        for (int height = 0; height < 3; ++height) {
            for (int width = 0; width < 3; ++width) {
                fprintf(stdout, "%c", cell[depth][height][width] ? '#' : '.');
            }
            putchar('\n');
        }
        putchar('\n');
    }


    return (0);
}
