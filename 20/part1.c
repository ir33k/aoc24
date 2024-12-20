#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

enum {
	TRACT = '.',
	START = 'S',
	END   = 'E',
	WALL  = '#',
	CHEAT = 'X',
	PATH  = 'O',
};

static char map[256][256];
static int steps[256][256];
static int w=0,h=0;
static int cheat=0;

static void print_map(void) {
	int x,y;
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		printf("%c", map[y][x]);
	}
}

static int walk(int x, int y, int step) {
	int n=0, result=INT_MAX;
	if (x<0 || x>=w-1 || y<0 || y>=h) {
		return 0;
	}
	switch (map[y][x]) {
	case '\n':  return 0;
	case END:   return step;
	case CHEAT:
		if (cheat) {
			if (steps[y][x] > step) {
				cheat = 0;
				goto again;
			}
		}
		return 0;
	case WALL:
		if (cheat) {
			cheat = 0;
			map[y][x] = CHEAT;
			break;
		}
		return 0;
	}
	if (steps[y][x] < step) {
		return 0;
	}
again:
	steps[y][x] = step;
	n = walk(x+1, y, step+1); if (n && n < result) result = n;
	n = walk(x-1, y, step+1); if (n && n < result) result = n;
	n = walk(x, y+1, step+1); if (n && n < result) result = n;
	n = walk(x, y-1, step+1); if (n && n < result) result = n;
	return result == INT_MAX ? 0 : result;
}

int main(void) {
	int x=0,y=0, sx=0,sy=0, limit=0;
	int i, n, max;
	int result=0;
	scanf("limit=%d\n", &limit);
	// Load map, set height and width
	while (fgets(map[h], sizeof map[0], stdin)) h++;
	while (*map[w++]);
	// Find start
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		steps[y][x] = INT_MAX;
		if (map[y][x] == START) {
			sx=x;
			sy=y;
		}
	}
	//
	cheat = 0;
	max = walk(sx, sy, 0);
	assert(max == 9376 || max == 84);
	for (i=1; i<max*4; i++) {
		for (y=0; y<h; y++)
		for (x=0; x<w; x++) {
			if (map[y][x] == TRACT) {
				steps[y][x] = INT_MAX;
			}
		}
		cheat = 1;
		n = walk(sx, sy, 0);
		result += (max - n >= limit);
	}
	printf("%d\n", result);
	return !(result == 1452 || result == 44);
}
