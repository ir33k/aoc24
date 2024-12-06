#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {UP, RIGHT, DOWN, LEFT, _COUNT};	// Directions

int
main(void)
{
	unsigned result;
	char map[256][256];	// Map with [y][x] coordinates
	int w,h;	// Map size
	int x,y, dx,dy, dir;	// Guard current and delta position and walking direction
	int gx,gy, ox,oy;	// Guard original position and obstacle position
	// Get map with height and width
	for (h=0; fgets(map[h], sizeof map[0], stdin); h++);
	w = strlen(map[0]) -1;	// -1 for '\n' character at the end of the line
	// Find guard starting position.
	for (gy=0; gy<h; gy++)
	for (gx=0; gx<w; gx++) {
		if (map[gy][gx] == '^') {
			goto found;
		}
	}
found:	result = 0;
	// Put new obstacle in each free space and walk the guard
	for (oy=0; oy<h; oy++)
	for (ox=0; ox<w; ox++) {
		if (map[oy][ox] != '.') {
			// Can't put new obstacle in already taken place
			// or at guard position.
			continue;
		}
		map[oy][ox] = '#';	// Put obstacle
		// Walk the guard.
		dir = UP;
		x = gx;
		y = gy;
		while (x<w && x>=0 && y<h && y>=0) {
			if (map[y][x] == dir) {
				// I was already here walking in the
				// same direction.  We found a loop.
				result ++;
				break;
			}
			if (map[y][x] == '.') {
				map[y][x] = dir;	// Remember direction
			}
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
		// Restore map
		for (y=0; y<h; y++)
		for (x=0; x<w; x++) {
			if (map[y][x] < _COUNT) {
				map[y][x] = '.';
			}
		}
		map[oy][ox] = '.';
		map[gy][gx] = '^';
	}
	printf("%u\n", result);
	return 0;
}
