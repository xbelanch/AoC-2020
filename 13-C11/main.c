#include <stdlib.h>
#include <stdio.h>

int solve_file(char *filename) {
    printf("Input file: %s\n", filename);
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        perror("File opening failed\n");
        return EXIT_FAILURE;
    }

    // read input file content
    const size_t line_size = 300;
    char *line = (char*)malloc(sizeof(char) * line_size);
    while (fgets(line, 300, fp) != NULL) {
        printf(line);
    }

    free(line);
    fclose(fp);
    return 0;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
