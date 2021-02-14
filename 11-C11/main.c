#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 4096

void solve_file(char *filename) {
    printf("Input file: %s\n", filename);

    char *arr[N + 1];
    int arr_size = 0;
    FILE *f = fopen(filename, "rb");
    while (!feof(f)) {
        char buffer[N + 1];
        arr[arr_size] = malloc(sizeof(char) * N);
        fscanf(f, "%[^\n]%*c", buffer);
        strcpy(arr[arr_size++], buffer);
    }

    fclose(f);

    // Print the seat layout
    printf("Rows: %d\n", arr_size - 1);
    for (int i = 0; i < arr_size - 1; i++) {
        for (int j = 0; arr[i][j]; j++) {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
