#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_LINE 512

int countlines(char *filename){
  int lines = 0;
  FILE* fp = fopen(filename, "r");

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

  FILE *fp = fopen(filename, "r");
  int max = countlines(filename);
  char **lines = (char**)malloc(sizeof(char*) * max);

  printf("Filename: %s\n", filename);
  printf("Number of lines of %s file: %d\n", filename, max);

  // store all the lines from input filename to lines var
  for (int i = 0; i < max; i++) {
    lines[i] = (char *)malloc(MAX_BUFFER_LINE);
    if (fgets(lines[i], MAX_BUFFER_LINE + 1, fp) == NULL) {
      printf("ERROR, line too long at %d\n", i);
    } else {
      printf("%d>%s", i, lines[i]);
    }
  }
  fclose(fp);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        solve_file(argv[i]);
    }
    return 0;
}
