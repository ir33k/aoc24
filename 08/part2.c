#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char map[256][256];	// Map with [y][x] coordinates
static int w,h;			// Map size

struct antena {
	struct antena *next;	// Linked list, an elegant weapon
	int x,y;
};

static void
add_antinodes(struct antena *a, struct antena *b)
{
	int dx = a->x - b->x;
	int dy = a->y - b->y;
	int x = a->x;
	int y = a->y;
	map[y][x] = 0;
	for (x+=dx, y+=dy; x>=0 && x<w && y>=0 && y<h; x+=dx, y+=dy) {
		map[y][x] = 0;
	}
}

int
main(void)
{
	int x,y, c, result;
	struct antena *node, *child, *antenas[128]={0};
	// Get map with height and width
	for (h=0; fgets(map[h], sizeof map[0], stdin); h++);
	w = strlen(map[0]) -1;	// -1 for '\n' character at the end of the line
	// Gather antenas
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		c = map[y][x];
		if (c == '.') {
			continue;
		}
		child = malloc(sizeof *child);	// Let it leak
		child->next = 0;
		child->x = x;
		child->y = y;
		if (antenas[c]) {
			for (node = antenas[c]; node->next; node = node->next);
			node->next = child;
		} else {
			antenas[c] = child;
		}
	}
	// Place antinodes for each antena type pair
	result = 0;
	for (c=0; c<128; c++) {
		for (node = antenas[c]; node && node->next; node = node->next)
		for (child = node->next; child; child = child->next) {
			add_antinodes(node, child);
			add_antinodes(child, node);
		}
	}
	// Count antiantenas
	result = 0;
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		result += !map[y][x];
	}
	printf("%d\n", result);
	return 0;
}
