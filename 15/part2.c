#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

enum {
	EMPTY = '.',
	ROBOT = '@',
	WALL  = '#',
	BOX   = 'O',
	BOX_L = '[',
	BOX_R = ']',
	UP    = '^',
	RIGHT = '>',
	DOWN  = 'v',
	LEFT  = '<',
};

static char map[256][256];	// [y][x]
static int w,h;			// Map size

static int move_horizontal(int x, int y, int dx) {
	int tmp;
	if (map[y][x+dx] == BOX_L ||
	    map[y][x+dx] == BOX_R) {
		move_horizontal(x+dx, y, dx);
	}
	if (map[y][x+dx] != EMPTY) {
		return 0;
	}
	tmp = map[y][x+dx];
	map[y][x+dx] = map[y][x];
	map[y][x] = tmp;
	return 1;
}

static int can_move_vertical(int x, int y, int dy) {
	switch (map[y][x]) {
	case BOX_L:
		if (map[y+dy][x] == BOX_L ||
		    map[y+dy][x] == BOX_R) {
			if (!can_move_vertical(x, y+dy, dy)) {
				return 0;
			}
		}
		if (map[y+dy][x+1] == BOX_L ||
		    map[y+dy][x+1] == BOX_R) {
			if (!can_move_vertical(x+1, y+dy, dy)) {
				return 0;
			}
		}
		if (map[y+dy][x]   == WALL ||
		    map[y+dy][x+1] == WALL) {
			return 0;
		}
		return 1;
	case BOX_R:
		if (map[y+dy][x] == BOX_L ||
		    map[y+dy][x] == BOX_R) {
			if (!can_move_vertical(x, y+dy, dy)) {
				return 0;
			}
		}
		if (map[y+dy][x-1] == BOX_L ||
		    map[y+dy][x-1] == BOX_R) {
			if (!can_move_vertical(x-1, y+dy, dy)) {
				return 0;
			}
		}
		if (map[y+dy][x]   == WALL ||
		    map[y+dy][x-1] == WALL) {
			return 0;
		}
		return 1;
	case EMPTY:
		return 1;
	}
	return 0;
}

static void move_vertical(int x, int y, int dy) {
	int tmp;
	switch (map[y][x]) {
	case ROBOT:
		if (map[y+dy][x] == BOX_L ||
		    map[y+dy][x] == BOX_R) {
			move_vertical(x, y+dy, dy);
		}
		break;
	case BOX_L:
		if (map[y+dy][x] == BOX_L ||
		    map[y+dy][x] == BOX_R) {
			move_vertical(x, y+dy, dy);
		}
		if (map[y+dy][x+1] == BOX_L ||
		    map[y+dy][x+1] == BOX_R) {
			move_vertical(x+1, y+dy, dy);
		}
		break;
	case BOX_R:
		if (map[y+dy][x] == BOX_L ||
		    map[y+dy][x] == BOX_R) {
			move_vertical(x, y+dy, dy);
		}
		if (map[y+dy][x-1] == BOX_L ||
		    map[y+dy][x-1] == BOX_R) {
			move_vertical(x-1, y+dy, dy);
		}
		break;
	}
	switch (map[y][x]) {
	case ROBOT:
		tmp = map[y+dy][x];
		map[y+dy][x] = map[y][x];
		map[y][x] = tmp;
		break;
	case BOX_L:
		tmp = map[y+dy][x];
		map[y+dy][x] = map[y][x];
		map[y][x] = tmp;
		tmp = map[y+dy][x+1];
		map[y+dy][x+1] = map[y][x+1];
		map[y][x+1] = tmp;
		break;
	case BOX_R:
		tmp = map[y+dy][x];
		map[y+dy][x] = map[y][x];
		map[y][x] = tmp;
		tmp = map[y+dy][x-1];
		map[y+dy][x-1] = map[y][x-1];
		map[y][x-1] = tmp;
		break;
	}
}

int main(int argc, char **argv) {
	char *tile=0;
	int x,y, dx,dy, direction;
	long unsigned result;
	FILE *fp;
	(void)argc;
	fp = fopen(argv[1], "r");
	if (!fp) {
		fprintf(stderr, "no file\n");
		return 1;
	}
	// Get map
	for (h=0; fgets(map[h], sizeof map[0], fp); h++) {
		if (map[h][0] == '\n') {
			break;
		}
	}
	w = strlen(map[0]) -1;	// -1 for '\n' character at the end of the line
	x=0;
	y=0;
	// Scale map
	for (y=0; y<h; y++)
	for (x=w-1; x>=0; x--) {
		switch (map[y][x]) {
		case WALL:  tile = "##"; break;
		case BOX:   tile = "[]"; break;
		case EMPTY: tile = ".."; break;
		case ROBOT: tile = "@."; break;
		}
		map[y][x*2+0] = tile[0];
		map[y][x*2+1] = tile[1];
	}
	w*=2;
	//
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		if (map[y][x] == ROBOT) {
			goto found;
		}
	}
found:
	while ((direction = getc(fp)) != EOF) {
		switch (direction) {
		case UP:    dx= 0; dy=-1; break;
		case RIGHT: dx=+1; dy= 0; break;
		case DOWN:  dx= 0; dy=+1; break;
		case LEFT:  dx=-1; dy= 0; break;
		default:
			continue;
		}
		switch (direction) {
		case UP:
		case DOWN:
			if (can_move_vertical(x, y+dy, dy)) {
				move_vertical(x, y, dy);
				y+=dy;
			}
			break;
		case RIGHT:
		case LEFT:
			if (move_horizontal(x, y, dx)) {
				x+=dx;
			}
			break;
		}
	}
	result = 0;
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		if (map[y][x] == BOX_L) {
			result += y*100 + x;
		}
	}
	printf("%lu\n", result);
	return result != 1399772;
}
