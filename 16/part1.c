#include <stdio.h>
#include <string.h>
#include <limits.h>

enum {
	// Map        Directions
	EMPTY = '.',  NORTH = '^',
	WALL  = '#',  EAST  = '>',
	START = 'S',  SAUTH = 'v',
	END   = 'E',  WEST  = '<',
};

static char map[256][256];
static int scores[256][256];
static int w=0,h=0;

static void walk(int x, int y, int dir, int score) {
	if (map[y][x] == WALL || scores[y][x] < score) {
		return;
	}
	scores[y][x] = score;
	switch (dir) {
	case NORTH:
		walk(x  , y-1, NORTH, score+1);
		walk(x+1, y  , EAST,  score+1001);
		walk(x-1, y  , WEST,  score+1001);
		break;
	case EAST:
		walk(x+1, y  , EAST,  score+1);
		walk(x  , y-1, NORTH, score+1001);
		walk(x  , y+1, SAUTH, score+1001);
		break;
	case SAUTH:
		walk(x  , y+1, SAUTH, score+1);
		walk(x+1, y  , EAST,  score+1001);
		walk(x-1, y  , WEST,  score+1001);
		break;
	case WEST:
		walk(x-1, y  , WEST,  score+1);
		walk(x  , y-1, NORTH, score+1001);
		walk(x  , y+1, SAUTH, score+1001);
		break;
	}
}

int main(void) {
	int x=0,y=0, sx=0,sy=0, ex=0,ey=0;
	// Load map, set height and width
	while (fgets(map[h], sizeof map[0], stdin)) h++;
	while (*map[w++]);
	// Find start
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		scores[y][x] = INT_MAX;
		if (map[y][x] == START) { sx=x; sy=y; }
		if (map[y][x] == END)   { ex=x; ey=y; }
	}
	x=sx;
	y=sy;
	walk(x+1, y  , EAST,  1);
	walk(x  , y-1, NORTH, 1001);
	walk(x  , y+1, SAUTH, 1001);
	printf("%d\n", scores[ey][ex]);
	return 0;
}
