#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Use lowercase letters to mark visited plants
#define TO_UPPER(c)	(0xDF & c)
#define TO_LOWER(c)	(0x20 | c)
#define IS_LOWER(c)	(0x20 & c)

static char map[256][256];	// Map with [y][x] coordinates
static int w,h;			// Map size

static struct point {
	int x,y;
} stack[1024];			// trust me bro, this is enough
static unsigned si;		// Stack index

static int check(int plant, int x, int y) {
	if (x<0 || x>=w || y<0 || y>=h || TO_UPPER(map[y][x]) != plant) {
		return 1;	// Outside of plant border
	}
	stack[si].x = x;
	stack[si].y = y;
	si++;
	assert(si < sizeof stack / sizeof stack[0]);
	return 0;
}

int main(void) {
	int x,y;		// Current position
	int plant, area, perimeter;
	long unsigned result;
	//
	for (h=0; fgets(map[h], sizeof map[0], stdin); h++);
	w = strlen(map[0]) -1;	// -1 for '\n' character at the end of the line
	//
	x = 0;
	y = 0;
	result = 0;
	while (1) {
		plant = map[y][x];
		area = 0;
		perimeter = 0;
		si = 0;
		stack[si].x = x;
		stack[si].y = y;
		do {
			x = stack[si].x;
			y = stack[si].y;
			if (IS_LOWER(map[y][x])) {
				continue;
			}
			area++;
			map[y][x] = TO_LOWER(plant);	// Mark as visited
			perimeter += check(plant, x  , y+1);
			perimeter += check(plant, x  , y-1);
			perimeter += check(plant, x+1, y  );
			perimeter += check(plant, x-1, y  );
		} while (si--);
		result += area * perimeter;
		// Find next plant
		for (y=0; y<h; y++)
		for (x=0; x<w; x++) {
			if (!IS_LOWER(map[y][x])) {
				goto next;
			}
		}
		break;	// No more plants
	next:	continue;
	}
	printf("%lu\n", result);
	return 0;
}
