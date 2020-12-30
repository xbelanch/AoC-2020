#include <stdio.h>
#include <stdlib.h>

int countlines(char *filename){
  int lines = 0;
  FILE* fp = fopen(filename, "rb");

  while(!feof(fp)) {
    char ch = fgetc(fp);
    if(ch == '\n') {
      lines++;
    }
  }
  fclose(fp);
  return lines;
}


void solve_file(char* filename) {
    printf("Filename: %s\n", filename);
    int max = countlines(filename);
    printf("Number of lines of %s file: %d\n", filename, max);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
