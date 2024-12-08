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
	int x,y;
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
		for (; node->next; node = node->next)
		for (pair = node->next; pair; pair = pair->next) {
			x = node->x + (node->x - pair->x);
			y = node->y + (node->y - pair->y);
			if (x>=0 && x<w && y>=0 && y<h && map[y][x] != '#') {
				map[y][x] = '#';
				result++;
			}
			x = pair->x + (pair->x - node->x);
			y = pair->y + (pair->y - node->y);
			if (x>=0 && x<w && y>=0 && y<h && map[y][x] != '#') {
				map[y][x] = '#';
				result++;
			}
		}
	}
	printf("%u\n", result);
	return 0;
}
