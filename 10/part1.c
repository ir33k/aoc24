#include <assert.h>
#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *
stringify(unsigned num, unsigned base, unsigned lpad)
{
	static char buf[16];
	unsigned i = sizeof buf;
	assert(sizeof buf > lpad);
	buf[--i] = 0;
	while (num && lpad--) {
		buf[--i] = num % base + '0';
		num /= base;
	}
	while (lpad--) {	// Left pad
		buf[--i] = '0';
	}
	return buf + i;
}

int main(void) {
	char map[256][256];	// Map with [y][x] coordinates
	int w,h;		// Map size
	int x,y;		// Current position
	int hx,hy;		// Trailhead coordinates
	int max;		// Max number of path permutations
	int i,j;		// General indexes
	char *path;		// Current path
	unsigned result;
	int *visited, visited_count;	// List of visited desitnations
	//
	for (h=0; fgets(map[h], sizeof map[0], stdin); h++);
	w = strlen(map[0]) -1;	// -1 for '\n' character at the end of the line
	//
	max = pow(4, 9);
	visited = malloc(max * (sizeof *visited));
	result = 0;
	for (hy=0; hy<h; hy++)
	for (hx=0; hx<w; hx++) {
		if (map[hy][hx] != '0') {
			continue;
		}
		visited_count = 0;
		for (i=0; i<max; i++) {
			x = hx;
			y = hy;
			path = stringify(i, 4, 9);
			for (j=0; path[j]; j++) {
				switch (path[j]) {
				case '0': y--; break;
				case '1': x++; break;
				case '2': y++; break;
				case '3': x--; break;
				}
				if (x<0 || x>=w || y<0 || y>=h ||
				    map[y][x] != j+1+'0') {
					goto skip;
				}
			}
			for (j=0; j<visited_count; j++) {
				if (visited[j] == y*w+x) {
					goto skip;
				}
			}
			visited[visited_count++] = y*w+x;
			result++;
		skip:
			continue;
		}
	}
	printf("%u\n", result);
	return 0;
}
