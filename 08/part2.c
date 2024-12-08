#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct antena_t {
	struct antena_t *next;
	int x,y;
};

int
main(void)
{
	int i,c;
	char map[256][256];	// Map with [y][x] coordinates
	int w,h;	// Map size
	int antena_map[128]={0};	// ASCII indexed map to antenas indexes
	struct antena_t *new, *node, *pair, *antenas[256]={0};
	int x,y, dx,dy;
	unsigned result;
	result = 0;
	// Get map with height and width
	for (h=0; fgets(map[h], sizeof map[0], stdin); h++);
	w = strlen(map[0]) -1;	// -1 for '\n' character at the end of the line
	// Gather antenas
	i=1;
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		c = map[y][x];
		if (c != '.') {
			if (!antena_map[c]) {
				antena_map[c] = i++;
			}
			new = malloc(sizeof *new);
			new->next = 0;
			new->x = x;
			new->y = y;
			node = antenas[antena_map[c]];
			if (!node) {
				antenas[antena_map[c]] = new;
			} else {
				for (; node->next; node = node->next);
				node->next = new;
			}
		}
	}
	// Go over each antena type
	for (c=0; c < 128; c++) {
		if (!antena_map[c]) {
			continue;
		}
		node = antenas[antena_map[c]];
		for (; node->next; node = node->next) {
			for (pair = node->next; pair; pair = pair->next) {
				dx = node->x - pair->x;
				dy = node->y - pair->y;
				x = node->x;
				y = node->y;
				map[y][x] = '#';
				x += dx;
				y += dy;
				while (x>=0 && x<w && y>=0 && y<h) {
					map[y][x] = '#';
					x += dx;
					y += dy;
				}
				dx = pair->x - node->x;
				dy = pair->y - node->y;
				x = pair->x;
				y = pair->y;
				map[y][x] = '#';
				x += dx;
				y += dy;
				while (x>=0 && x<w && y>=0 && y<h) {
					map[y][x] = '#';
					x += dx;
					y += dy;
				}
			}
		}
	}
	// Count antiantenas
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		result += map[y][x] == '#';
	}
	printf("%u\n", result);
	return 0;
}
