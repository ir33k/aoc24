#include <assert.h>
#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
	int dx,dy;		// Delta position of next move
	int max;		// Max number of path permutations
	int i,j;		// General indexes
	char *path;		// Current path
	unsigned result;
	//
	for (h=0; fgets(map[h], sizeof map[0], stdin); h++);
	w = strlen(map[0]) -1;	// -1 for '\n' character at the end of the line
	//
	max = pow(4, 9);
	result = 0;
	dx = 0;
	dy = 0;
	for (hy=0; hy<h; hy++)
	for (hx=0; hx<w; hx++) {
		if (map[hy][hx] != '0') {
			continue;
		}
		for (i=0; i<max; i++) {
			x = hx;
			y = hy;
			path = stringify(i, 4, 9);
			for (j=0; path[j]; j++) {
				switch (path[j]) {
				case '0': dx= 0; dy=-1; break;
				case '1': dx=+1; dy= 0; break;
				case '2': dx= 0; dy= 1; break;
				case '3': dx=-1; dy= 0; break;
				}
				x += dx;
				y += dy;
				if (x<0 || x>=w || y<0 || y>=h ||
				    map[y][x] != j+1+'0') {
					x -= dx;
					y -= dy;
					goto skip;
				}
			}
			result++;
		skip:
			continue;
		}
	}
	printf("%u\n", result);
	return 0;
}
