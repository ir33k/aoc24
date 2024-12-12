#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point { int x,y; };

static char map[256][256];	// Map with [y][x] coordinates
static char visited[256][256]={0};
static int w,h;		// Map size

static int is_border(int plant, int x, int y)
{
	return x<0 || x>=w || y<0 || y>=h || map[y][x] != plant;
}

int main(void) {
	int x,y;		// Current position
	int dx,dy;
	int plant;
	unsigned i;
	unsigned area;
	unsigned perimeter;
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
		i++;
		while (i--) {
			x = stack[i].x;
			y = stack[i].y;
			if (visited[y][x]) {
				continue;
			}
			area++;
			visited[y][x] = 1;
			//
			dx=x+0; dy=y+1;
			border = is_border(plant, dx, dy);
			if (!border && !visited[dy][dx]) {
				stack[i].x = dx;
				stack[i].y = dy;
				i++;
			} else {
				perimeter += border;
			}
			//
			dx=x+0; dy=y-1;
			border = is_border(plant, dx, dy);
			if (!border && !visited[dy][dx]) {
				stack[i].x = dx;
				stack[i].y = dy;
				i++;
			} else {
				perimeter += border;
			}
			//
			dx=x+1; dy=y+0;
			border = is_border(plant, dx, dy);
			if (!border && !visited[dy][dx]) {
				stack[i].x = dx;
				stack[i].y = dy;
				i++;
			} else {
				perimeter += border;
			}
			//
			dx=x-1; dy=y+0;
			border = is_border(plant, dx, dy);
			if (!border && !visited[dy][dx]) {
				stack[i].x = dx;
				stack[i].y = dy;
				i++;
			} else {
				perimeter += border;
			}
		}
		//
		result += area * perimeter;
		// Find next plant
		for (y=0; y<h; y++)
		for (x=0; x<w; x++) {
			if (!visited[y][x]) {
				goto next;
			}
		}
		// No more plants
		break;
	next:
		// We found next plant
		continue;
	}
	printf("%lu\n", result);
	return 0;
}
