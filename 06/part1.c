#include <stdio.h>
#include <string.h>

enum {UP, RIGHT, DOWN, LEFT, _COUNT};	// Directions

int main(void) {
	unsigned result;
	char map[256][256];	// Map with [y][x] coordinates
	int w,h;	// Map size
	int x,y, dx,dy, dir;	// Guard current and delta position and walking direction
	// Get map with height and width
	for (h=0; fgets(map[h], sizeof map[0], stdin); h++);
	w = strlen(map[0]) -1;	// -1 for '\n' character at the end of the line
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		if (map[y][x] == '^') {
			goto found;	// Found guard starting position
		}
	}
found:	// Walk the guard.
	result = 0;
	dir = UP;	// Initial direction is always UP
	while (x<w && x>=0 && y<h && y>=0) {
		result += map[y][x] != 'X';
		map[y][x] = 'X';
		switch (dir) {
		case UP:    dx= 0; dy=-1; break;
		case RIGHT: dx=+1; dy= 0; break;
		case DOWN:  dx= 0; dy=+1; break;
		case LEFT:  dx=-1; dy= 0; break;
		}
		x+=dx; y+=dy;	// Apply delta position
		if (map[y][x] == '#') {
			x-=dx; y-=dy;	// Go back one step
			dir = (dir+1) % _COUNT;	// Turn right by switching to next direction
		}
	}
	printf("%u\n", result);
	return 0;
}
