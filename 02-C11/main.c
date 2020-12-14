#include <stdlib.h>
#include <stdio.h>

void parseInput(char* filename)
{
    int min, max;
    char ch;
    char str[100];
    char pattern[256];
    FILE *file;

    if ((file = fopen(filename, "r")) == NULL) {
        printf("ERROR:: opening file %s\n", filename);
        exit(-1);
    }
    // reads text until new line is encountered
    // https://medium.com/@zoha131/fun-with-scanf-in-c-3d7a8d310229
    // parse the numbers of the input text file

    fscanf(file, "%1d%*c%1d%*c%1c%*2c%s", &min, &max, &ch, str);

    // Create the password pattern only for testing purpose
    snprintf(pattern, 256, "%d-%d %c: %s", min, max, ch, str);

    printf("Min: %d, Max: %d, Char: %c, String: %s\n", min, max, ch, str);

    int counter = 0;
    int repeated = 0;
    while (str[counter] != '\0') {
        printf("%c,", str[counter]);
        if (str[counter] == ch) repeated++;
        counter++;
    }

    if (repeated >=min && repeated <= max) {
        printf("Match!\n");
    } else {
        printf("Not matched: %s\n", pattern);
    }


    fclose(file);

}


int main(int argc, char *argv[])
{
    parseInput(argv[1]);
    return 0;
}
