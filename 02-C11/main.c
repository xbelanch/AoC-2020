#include <stdlib.h>
#include <stdio.h>

int parseInput(char* filename)
{
    int lines = 0;
    int valid = 0;
    int i, repeat;
    int min, max;
    char letter;
    char password[100];
    char entry[256];
    FILE *file;

    if ((file = fopen(filename, "r")) == NULL) {
        printf("ERROR:: opening file %s\n", filename);
        exit(-1);
    }
    // reads text until new line is encountered
    // https://medium.com/@zoha131/fun-with-scanf-in-c-3d7a8d310229
    // parse the numbers of the input text file
    while ( fscanf(file, "%2d%*c%2d%*c%1c%*2c%s", &min, &max, &letter, password)!= EOF) {
        lines++;
        // Create the password entry only for testing purpose
        snprintf(entry, 256, "%d-%d %c: %s", min, max, letter, password);

        // parse the password and count letter policy
        i = repeat = 0;
        while (password[i] != '\0') {
            if (password[i] == letter) repeat++;
            i++;
        }

        // check if number policy letter repeated on password is valid according
        // the min and max policy numbers
        if (repeat >=min && repeat <= max) valid++;
    }

    fclose(file);

    return valid;
}


int main(int argc, char *argv[])
{
    int valid = parseInput(argv[1]);
    printf("Valid passwords: %d\n", valid);

    return 0;
}
