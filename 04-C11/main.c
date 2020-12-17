#include <stdio.h>
#include <stdlib.h>

#define puts(string) printf("%s\n", string)

void parseInput(char* filename) {
    puts(filename);
}


int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        parseInput(argv[i]);
    }
    return 0;
}
