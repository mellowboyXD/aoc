#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  FILE *fptr = fopen("src/day2/input", "r");
  if (fptr == NULL) {
    fprintf(stderr, "Unable to open file");
    exit(1);
  }

  int l, w, h;
  int total_paper = 0;
  int total_ribbon = 0;

  while (fscanf(fptr, "%ix%ix%i\n", &l, &w, &h) != EOF) {
    int surface_area = 2 * l * w + 2 * l * h + 2 * w * h;
    int volume = l * w * h;

    int face_areas[3] = {l * w, l * h, w * h};
    int perimeter[3] = {2 * (l + w), 2 * (l + h), 2 * (w + h)};
    int smallest_perimeter = perimeter[0];
    int smallest_area = face_areas[0];

    for(int i = 0; i < 3; i++) {
      if (face_areas[i] < smallest_area)
        smallest_area = face_areas[i];
      if (perimeter[i] < smallest_perimeter)
        smallest_perimeter = perimeter[i];
    }

    total_ribbon += (volume + smallest_perimeter);
    total_paper += (surface_area + smallest_area);
  }
  fclose(fptr);

  printf("Total Wrapping Paper: %i\nTotal Ribbon: %i\n", total_paper,
         total_ribbon);
}
