#include <stdio.h>
#include <string.h>

enum {
	EMPTY = '.',
	ROBOT = '@',
	WALL  = '#',
	BOX   = 'O',
	TOP   = '^',
	RIGHT = '>',
	DOWN  = 'v',
	LEFT  = '<',
};

static char map[64][64];	// [y][x]
static int w,h;			// Map size

static int move(int x, int y, int dx, int dy) {
	int tmp;
	if (map[y+dy][x+dx] == BOX) {
		move(x+dx, y+dy, dx, dy);
	}
	if (map[y+dy][x+dx] != EMPTY) {
		return 0;
	}
	tmp = map[y+dy][x+dx];
	map[y+dy][x+dx] = map[y][x];
	map[y][x] = tmp;
	return 1;
}

int main(void) {
	int x=0,y=0, dx,dy, direction;
	long unsigned result;
	// Get map
	for (h=0; fgets(map[h], sizeof map[0], stdin); h++) {
		if (map[h][0] == '\n') {
			break;
		}
	}
	w = strlen(map[0]) -1;	// -1 for '\n' character at the end of the line
	// Find robot
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		if (map[y][x] == ROBOT) {
			goto found;
		}
	}
found:
	// Move robot
	while ((direction = getchar()) != EOF) {
		switch (direction) {
		case TOP:   dx= 0; dy=-1; break;
		case RIGHT: dx=+1; dy= 0; break;
		case DOWN:  dx= 0; dy=+1; break;
		case LEFT:  dx=-1; dy= 0; break;
		default: continue;	// Ignore other characters like \n
		}
		if (move(x, y, dx, dy)) {
			x+=dx;
			y+=dy;
		}
	}
	// Calculate boxes' BPS coordinates
	result = 0;
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		if (map[y][x] == BOX) {
			result += y*100 + x;
		}
	}
	printf("%lu\n", result);
	return 0;
}
