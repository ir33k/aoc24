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
	int x,y;	// Guard current position
	int gx,gy;	// Guard original position
	int ox,oy;	// Obstacle position
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
	gx=x; gy=y;	// Remember guard original position
	result = 0;
	// Put new obstacle in each free space
	for (oy=0; oy<h; oy++)
	for (ox=0; ox<w; ox++) {
		if (map[oy][ox] == '#' || (oy == gy && ox == gx)) {
			// Can't put new obstacle in already taken place
			// or at guard position.
			continue;
		}
		// Put obstacle.
		map[oy][ox] = 'O';
		// Walk the guard.
		while (x<w && x>=0 && y<h && y>=0) {
			if (map[y][x] == dir) {
				// I was already here walking in the
				// same direction.  We found a loop.
				result ++;
				break;
			}
			switch (map[y][x]) {
			case UP:
			case RIGHT:
			case DOWN:
			case LEFT:
				break;
			default:
				map[y][x] = dir;	// Remember direction
			}
			switch (dir) {
			case UP:    y--; break;
			case RIGHT: x++; break;
			case DOWN:  y++; break;
			case LEFT:  x--; break;
			}
			if (map[y][x] == '#' || map[y][x] == 'O') {
				switch (dir) {
				case UP:    y++; break;
				case RIGHT: x--; break;
				case DOWN:  y--; break;
				case LEFT:  x++; break;
				}
				dir = (dir + 1) % _DIR_COUNT;	// Turn right
			}
		}
		// Restore map
		for (y=0; y<h; y++)
		for (x=0; x<w; x++) {
			switch (map[y][x]) {
			case UP:
			case RIGHT:
			case DOWN:
			case LEFT:
			case 'O':
				map[y][x] = '.';
				break;
			}
		}
		// Restore guard original position
		dir = UP;
		x=gx; y=gy;
	}
	printf("%u\n", result);
	return 0;
}
