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
static char corners[256][256];	// To track corners or current region

static struct point {
	int x,y;
} stack[1024];			// trust me bro, this is enough
static unsigned si;		// Stack index

static int is_outside(int plant, int x, int y) {
	return x<0 || x>=w || y<0 || y>=h || TO_UPPER(map[y][x]) != plant;
}

static void maybe_corner(int plant, int x, int y, int i) {
	// d[i][diagonal_edge,side_edge,side_edge,corner_delta][x,y]
	static const int d[4][4][2]={			// Corners
		{{-1,-1},{-1, 0},{ 0,-1},{ 0, 0}},	// Top left
		{{+1,-1},{ 0,-1},{+1, 0},{+1, 0}},	// Top right
		{{ 1, 1},{+1, 0},{ 0,+1},{+1,+1}},	// Bottom right
		{{-1,+1},{-1, 0},{ 0,+1},{ 0,+1}}};	// Bottom left
	int edges=0, diagonal=0;
	if (is_outside(plant, x+d[i][0][0], y+d[i][0][1])) edges++;
	diagonal = edges;
	if (is_outside(plant, x+d[i][1][0], y+d[i][1][1])) edges++;
	if (is_outside(plant, x+d[i][2][0], y+d[i][2][1])) edges++;
	x += d[i][3][0];
	y += d[i][3][1];
	switch (edges) {
	case 1: corners[y][x] = 1; break;
	case 2: corners[y][x] += !diagonal; break;
	case 3: corners[y][x] = 1; break;
	}
}

static void check(int plant, int x, int y) {
	if (!is_outside(plant, x, y)) {
		stack[si].x = x;
		stack[si].y = y;
		assert(++si < sizeof stack / sizeof stack[0]);
	}
}

int main(void) {
	int x=0, y=0;		// Current position
	int plant, area, perimeter;
	long unsigned result=0;
	//
	for (h=0; fgets(map[h], sizeof map[0], stdin); h++);
	w = strlen(map[0]) -1;	// -1 for '\n' character at the end of the line
	//
	while (1) {
		plant = map[y][x];
		area = 0;
		si = 0;
		stack[si].x = x;
		stack[si].y = y;
		si++;
		while (si--) {
			x = stack[si].x;
			y = stack[si].y;
			if (IS_LOWER(map[y][x])) {
				continue;
			}
			area++;
			map[y][x] = TO_LOWER(plant);	// Mark as visited
			maybe_corner(plant, x, y, 0);
			maybe_corner(plant, x, y, 1);
			maybe_corner(plant, x, y, 2);
			maybe_corner(plant, x, y, 3);
			check(plant, x  , y+1);
			check(plant, x  , y-1);
			check(plant, x+1, y  );
			check(plant, x-1, y  );
		};
		perimeter = 0;
		for (y=0; y<h+1; y++)
		for (x=0; x<w+1; x++) {
			perimeter += corners[y][x];
			corners[y][x] = 0;
		}
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
