#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {UP=0, RIGHT, DOWN, LEFT, _DIR_COUNT};

int
main(void)
{
	int i, dir;
	unsigned result;
	char map[256][256];
	int w,h;	// Map size
	int x,y;	// Guard position
	for (i=0; fgets(map[i], sizeof map[i], stdin); i++);
	h = i;
	w = strlen(map[0]) - 1;
	// Find guard starting position.
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		if (map[y][x] == '^') {
			goto found;
		}
	}
found:
	// Walk the guard.
	result = 0;
	dir = UP;
	while (x<w && x>=0 && y<h && y>=0) {
		if (map[y][x] != 'X') {
			result++;
			map[y][x] = 'X';
		}
		switch (dir) {
		case UP:    y--; break;
		case RIGHT: x++; break;
		case DOWN:  y++; break;
		case LEFT:  x--; break;
		}
		if (map[y][x] == '#') {
			switch (dir) {
			case UP:    y++; break;
			case RIGHT: x--; break;
			case DOWN:  y--; break;
			case LEFT:  x++; break;
			}
			dir = (dir + 1) % _DIR_COUNT;	// Turn right
		}
	}
	printf("%u\n", result);
	return 0;
}
