#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define NORTH '^'
#define SOUTH 'v'
#define EAST '>'
#define WEST '<'

int main(void) {
  FILE *fptr = fopen("src/day3/input", "r");
  if (fptr == NULL) {
    fputs("Unable to open file.\n", stderr);
    exit(EXIT_FAILURE);
  }

  int token;
  while ((token = fgetc(fptr)) != EOF) {
    fprintf(stdout, "%c\n", token);
  }

  fclose(fptr);
  exit(EXIT_SUCCESS);
}
