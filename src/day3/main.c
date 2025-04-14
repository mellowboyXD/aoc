#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define NORTH '^'
#define SOUTH 'v'
#define EAST '>'
#define WEST '<'

typedef struct
{
  int x;
  int y;
} Point;

typedef enum
{
  false,
  true
} bool;

bool
alreadyVisited(Point* visited_houses, int size, Point coordinates)
{
  for (int i = 0; i < size; i++) {
    if (visited_houses[i].x == coordinates.x &&
        visited_houses[i].y == coordinates.y) {
      return true;
    }
  }
  return false;
}

bool
addVisited(Point* visited_houses, int* count, Point coordinates)
{
  (*count)++;
  Point* temp = visited_houses;
  visited_houses = realloc(visited_houses, (*count) * sizeof(Point));
  if (visited_houses == NULL) {
    visited_houses = temp;
    return false;
  }

  visited_houses[(*count) - 1] = coordinates;
  return true;
}

void
listAllVisited(Point* visited_houses, int count)
{
  for (int i = 0; i < count; i++) {
    printf("(%i, %i)\n", visited_houses[i].x, visited_houses[i].y);
  }
}

int
main(void)
{
  FILE* fptr = fopen("src/day3/input", "r");
  if (fptr == NULL) {
    perror("Unable to open file\n");
    exit(EXIT_FAILURE);
  }

  int count = 1;
  Point coordinates = { 0, 0 };
  Point* visited_houses = (Point*)malloc(count * sizeof(Point));
  if (visited_houses == NULL) {
    perror("An error occured\n");
    exit(EXIT_FAILURE);
  }
  visited_houses[0] = coordinates;

  int token;
  while ((token = fgetc(fptr)) != EOF) {
    switch (token) {
      case NORTH:
        coordinates.y++;
        break;
      case SOUTH:
        coordinates.y--;
        break;
      case EAST:
        coordinates.x++;
        break;
      case WEST:
        coordinates.x--;
        break;
    }
  }

  printf("Current coordinates: (%i, %i)\n", coordinates.x, coordinates.y);
  free(visited_houses);
  fclose(fptr);
  return 0;
}
