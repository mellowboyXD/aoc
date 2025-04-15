#include <stdio.h>
#include <stdlib.h>

#define NORTH '^'
#define SOUTH 'v'
#define EAST '>'
#define WEST '<'
#define NEWLINE '\n'

#define FIRST_HOUSE 0
#define BYTES 3 // fgets copies 2 bytes and adds '\0'
#define SANTA_TOK 0
#define ROBO_TOK 1

struct point {
	int x;
	int y;
};

enum boolean { false, true };

enum boolean check_visited(struct point *visited, int n,
			   struct point coordinates)
{
	for (int i = 0; i < n; i++) {
		if (visited[i].x == coordinates.x &&
		    visited[i].y == coordinates.y) {
			return true;
		}
	}
	return false;
}

void add_visited(struct point **visited, int *n, struct point pos)
{
	(*n)++;

	*visited = realloc(*visited, (*n) * sizeof(struct point));
	if (*visited == NULL) {
		perror("Unable to reallocate memory.\n");
		exit(EXIT_FAILURE);
	}

	(*visited)[(*n) - 1] = pos;
}

void list_visited(struct point *visited, int n)
{
	for (int i = 0; i < n; i++) {
		printf("%i. (%i, %i)\n", i + 1, visited[i].x, visited[i].y);
	}
}

void move(struct point *pos, char tok)
{
	switch (tok) {
	case NORTH:
		pos->y++;
		break;
	case SOUTH:
		pos->y--;
		break;
	case EAST:
		pos->x++;
		break;
	case WEST:
		pos->x--;
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

	int n = 1;
	struct point santa = { 0, 0 };
	struct point robo = { 0, 0 };

	struct point *visited =
		(struct point *)malloc(n * sizeof(struct point));
	if (visited == NULL) {
		perror("Could not allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	visited[FIRST_HOUSE] = santa;

	char buffer[BYTES];
	while ((fgets(buffer, BYTES, fptr)) != NULL) {
		char santa_c = buffer[SANTA_TOK];
		char robo_c = buffer[ROBO_TOK];

		// Skips newline
		if (santa_c == NEWLINE || robo_c == NEWLINE)
			break;

		move(&santa, santa_c);
		if (check_visited(visited, n, santa) == false) {
			add_visited(&visited, &n, santa);
		} else {
			printf("Already visited: (%i, %i)\n", santa.x, santa.y);
		}

		move(&robo, robo_c);
		if (check_visited(visited, n, robo) == false) {
			add_visited(&visited, &n, robo);
		} else {
			printf("Already visited: (%i, %i)\n", robo.x, robo.y);
		}
	}

	list_visited(visited, n);
	printf("Total visited houses: %i\n", n);

	free(visited);
	fclose(fptr);
	exit(EXIT_SUCCESS);
}
