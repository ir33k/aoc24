#include <assert.h>
#include <stdio.h>

#define ABS(a) ((a) < 0 ? -(a) : (a))

enum { TRACT='.', START='S', END='E', WALL='#' };

static char map[256][256];
static int w=0,h=0;
static struct { int x,y; } path[16384];	// [step]
static unsigned ps = 0;			// path size

static void walk(int x, int y) {
	if (map[y][x] == WALL) {
		return;
	}
	map[y][x] = WALL;	// Mark as visited
	path[ps].x = x;
	path[ps].y = y;
	assert(++ps < (sizeof path / sizeof path[0]));
	walk(x+1, y);
	walk(x-1, y);
	walk(x, y+1);
	walk(x, y-1);
}

int main(void) {
	unsigned i,j, result=0;
	int x=0,y=0, distance, saved, limit=0;
	scanf("limit=%d\n", &limit);
	// Load map, set height and width
	while (fgets(map[h], sizeof map[0], stdin)) h++;
	while (*map[w++]);
	// Find start
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		if (map[y][x] == START) {
			goto start;
		}
	}
start:	walk(x, y);
	assert(ps == 9377 || ps == 85);
	for (i=0; i<ps; i++)	// Index for start of the cheat
	for (j=i; j<ps; j++) {	// Index for end of the cheat
		x = ABS(path[i].x - path[j].x);
		y = ABS(path[i].y - path[j].y);
		distance = x + y;
		if (distance > 20) {
			continue;
		}
		saved = j-i - distance;
		result += saved >= limit;
	}
	printf("%d\n", result);
	return !(result == 999556 || result == 285);
}
