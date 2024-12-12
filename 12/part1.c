#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TO_UPPER(c)	(0xDF & c)
#define TO_LOWER(c)	(0x20 | c)
#define IS_LOWER(c)	(0x20 & c)

struct point { int x,y; };

static char map[256][256];	// Map with [y][x] coordinates
static int w,h;		// Map size

static int is_border(int plant, int x, int y)
{
	return x<0 || x>=w || y<0 || y>=h || TO_UPPER(map[y][x]) != plant;
}

int main(void) {
	int x,y;		// Current position
	int dx,dy;
	unsigned i, plant, area, perimeter;
	long unsigned result;
	int border;
	struct point stack[256];
	//
	for (h=0; fgets(map[h], sizeof map[0], stdin); h++);
	w = strlen(map[0]) -1;	// -1 for '\n' character at the end of the line
	//
	x = 0;
	y = 0;
	result = 0;
	while (1) {
		plant = map[y][x];
		area = 0;
		perimeter = 0;
		i = 0;
		stack[i].x = x;
		stack[i].y = y;
		do {
			x = stack[i].x;
			y = stack[i].y;
			if (IS_LOWER(map[y][x])) {
				continue;
			}
			area++;
			map[y][x] = TO_LOWER(plant);	// Mark as visited
			//
			dx=x+0; dy=y+1;
			border = is_border(plant, dx, dy);
			perimeter += border;
			if (!border && !IS_LOWER(map[dy][dx])) {
				stack[i].x = dx;
				stack[i].y = dy;
				i++;
			}
			//
			dx=x+0; dy=y-1;
			border = is_border(plant, dx, dy);
			perimeter += border;
			if (!border && !IS_LOWER(map[dy][dx])) {
				stack[i].x = dx;
				stack[i].y = dy;
				i++;
			}
			//
			dx=x+1; dy=y+0;
			border = is_border(plant, dx, dy);
			perimeter += border;
			if (!border && !IS_LOWER(map[dy][dx])) {
				stack[i].x = dx;
				stack[i].y = dy;
				i++;
			}
			//
			dx=x-1; dy=y+0;
			border = is_border(plant, dx, dy);
			perimeter += border;
			if (!border && !IS_LOWER(map[dy][dx])) {
				stack[i].x = dx;
				stack[i].y = dy;
				i++;
			}
		} while (i--);
		result += area * perimeter;
		// Find next plant
		for (y=0; y<h; y++)
		for (x=0; x<w; x++) {
			if (!IS_LOWER(map[y][x])) {
				goto next;
			}
		}
		break;	// No more plants
	next:	continue;
	}
	printf("%lu\n", result);
	return 0;
}
