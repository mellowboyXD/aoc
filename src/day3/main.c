#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define NORTH '^'
#define SOUTH 'v'
#define EAST '>'
#define WEST '<'
#define NEWLINE '\n'

#define FIRST_HOUSE 0
#define BYTES_CPY 3 // fgets copies 2 bytes and adds '\0'
#define SANTA_TOKEN_IDX 0
#define ROBO_TOKEN_IDX 1

typedef struct {
	int x;
	int y;
} Point;

typedef enum { false, true } bool;

bool alreadyVisited(Point visited_houses[], int count, Point coordinates)
{
	for (int i = 0; i < count; i++) {
		if (visited_houses[i].x == coordinates.x &&
		    visited_houses[i].y == coordinates.y) {
			return true;
		}
	}
	return false;
}

void addVisited(Point **visited_houses, int *count, Point coordinates)
{
	(*count)++;

	*visited_houses = realloc(*visited_houses, (*count) * sizeof(Point));
	if (visited_houses == NULL) {
		perror("Unable to reallocate memory.\n");
		exit(EXIT_FAILURE);
	}

	(*visited_houses)[(*count) - 1] = coordinates;
}

void listAllVisited(Point *visited_houses, int count)
{
	for (int i = 0; i < count; i++) {
		printf("%i. (%i, %i)\n", i + 1, visited_houses[i].x,
		       visited_houses[i].y);
	}
}

void move(Point *coordinates, char token)
{
	switch (token) {
	case NORTH:
		coordinates->y++;
		break;
	case SOUTH:
		coordinates->y--;
		break;
	case EAST:
		coordinates->x++;
		break;
	case WEST:
		coordinates->x--;
		break;
	}
}

int main(void)
{
	FILE *fptr = fopen("src/day3/input", "r");
	if (fptr == NULL) {
		perror("Unable to open file\n");
		exit(EXIT_FAILURE);
	}

	int count = 1;
	Point santa = { 0, 0 };
	Point robo_santa = { 0, 0 };

	Point *visited_houses = (Point *)malloc(count * sizeof(Point));
	if (visited_houses == NULL) {
		perror("Could not allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	visited_houses[FIRST_HOUSE] = santa;

	char token_buff[BYTES_CPY];
	while ((fgets(token_buff, BYTES_CPY, fptr)) != NULL) {
		char santa_token = token_buff[SANTA_TOKEN_IDX];
		char robo_token = token_buff[ROBO_TOKEN_IDX];

		// Skips newline
		if (santa_token == NEWLINE || robo_token == NEWLINE)
			break;

		move(&santa, santa_token);
		if (alreadyVisited(visited_houses, count, santa) == false) {
			addVisited(&visited_houses, &count, santa);
		} else {
			printf("Santa: already visited: (%i, %i)\n", santa.x,
			       santa.y);
		}

		move(&robo_santa, robo_token);
		if (alreadyVisited(visited_houses, count, robo_santa) ==
		    false) {
			addVisited(&visited_houses, &count, robo_santa);
		} else {
			printf("Robo-Santa: already visited: (%i, %i)\n",
			       robo_santa.x, robo_santa.y);
		}
	}

	listAllVisited(visited_houses, count);
	printf("Total visited houses: %i\n", count);

	free(visited_houses);
	fclose(fptr);
	exit(EXIT_SUCCESS);
}
