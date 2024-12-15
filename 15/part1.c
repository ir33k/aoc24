#include <stdio.h>

enum {
	EMPTY = '.',
	ROBOT = '@',
	WALL  = '#',
	BOX   = 'O',
	UP    = '^',
	RIGHT = '>',
	DOWN  = 'v',
	LEFT  = '<',
};

static char map[64][64];	// [y][x]
static int w=0,h=0;		// Map size

static void print_map(int robot) {
	int x,y;
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		putchar(map[y][x] == ROBOT ? robot : map[y][x]);
	}
}

static int move(int x, int y, int dx, int dy) {
	if (map[y+dy][x+dx] == BOX) {
		move(x+dx, y+dy, dx, dy);
	}
	if (map[y+dy][x+dx] != EMPTY) {
		return 0;
	}
	map[y+dy][x+dx] = map[y][x];
	map[y][x] = EMPTY;
	return 1;
}

int main(void) {
	int x=0,y=0, dx,dy, direction;
	long unsigned result;
	// Load map, set height and width
	while (fgets(map[h], sizeof map[0], stdin) && map[h][0] != '\n') h++;
	while (*map[++w]);
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
		case UP:    dx= 0; dy=-1; break;
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
	print_map(ROBOT);
	// Calculate boxes' GPS coordinates
	result = 0;
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		if (map[y][x] == BOX) {
			result += y*100 + x;
		}
	}
	printf("%lu\n", result);
	return result != 1413675;
}
