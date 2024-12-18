#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

int usleep(unsigned);

enum {
	SAFE=0,
	CORRUPTED,
	CHECKED,
	VISITED,
	PATH,
};

static int map[128][128]={0};
static int w,h;

#define STACK_SIZE 1024*8
static struct {
	int x,y;
	int parent;
	int steps;
	float distance;
} stack[STACK_SIZE];
static int si={0};

static void clear_screen(void)
{
	/**
	 * Esc    - Escape code (0x1B)
	 * Esc[H  - Cursor Home
	 * Esc[2J - Erase Screen
	 */
	fputs("\x1B[H" "\x1B[2J", stdout);
	fflush(stdout);
}

static void print_map(void) {
	int x,y;
	fputs("\x1B[H", stdout);
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			switch (map[y][x]) {
			case SAFE:      printf("."); break;
			case CORRUPTED: printf(" "); break;
			case VISITED:   printf("+"); break;
			case PATH:      printf("#"); break;
			}
		}
		printf("\n");
	}
	usleep(1000000/240);	// FPS
}

static void stack_push(int x, int y, int parent, int steps) {
	assert(si+1 < STACK_SIZE);
	stack[si].x = x;
	stack[si].y = y;
	stack[si].parent = parent;
	stack[si].steps = steps;
	x = w-x;
	y = h-y;
	stack[si].distance = sqrtf(x*x + y*y);
	si++;
}

static int stack_get_closest(void) {
	int i,j;
	for (j=0; j<si; j++) {
		if (map[stack[j].y][stack[j].x] != VISITED) {
			break;
		}
	}
	for (i=0; i<si; i++) {
		if (map[stack[i].y][stack[i].x] == VISITED) {
			continue;
		}
		if ((float)stack[i].steps + stack[i].distance ==
		    (float)stack[j].steps + stack[j].distance) {
			if (stack[i].distance < stack[j].distance) {
				j = i;
			}
			continue;
		}
		if ((float)stack[i].steps + stack[i].distance <
		    (float)stack[j].steps + stack[j].distance) {
			j = i;
		}
	}
	assert(map[stack[j].y][stack[j].x] != VISITED);
	return j;
}

static int stack_get(int x, int y) {
	int i;
	for (i=0; i<si; i++) {
		if (stack[i].x == x && stack[i].y == y) {
			return i;
		}
	}
	return -1;
}

static void on_neighbour(int x, int y, int parent, int steps) {
	int i;
	if (x<0 || x>=w || y<0 || y>= h) {
		return;
	}
	switch (map[y][x]) {
	case VISITED:
		return;
	case SAFE:
		stack_push(x, y, parent, steps);
		return;
	case CHECKED:
		i = stack_get(x, y);
		assert(i != -1);
		if (stack[i].steps > steps) {
			stack[i].steps = steps;
			stack[i].parent = parent;
		}
		break;
	}
}

int main(void) {
	int i, x,y, steps, bytes, result;
	// NOTE(irek): I stored size and bytes in input
	scanf("w=%d h=%d bytes=%d\n", &w, &h, &bytes);
	while (bytes-- && scanf("%d,%d\n", &x, &y) != EOF) {
		map[y][x] = CORRUPTED;
	}
	result = 0;
	stack_push(0, 0, -1, 0);
	clear_screen();
	while (1) {
		i = stack_get_closest();
		x = stack[i].x;
		y = stack[i].y;
		steps = stack[i].steps;
		if (x == w-1 && y == h-1) {
			break;
		}
		map[y][x] = VISITED;
		on_neighbour(x+1, y, i, steps+1);
		on_neighbour(x-1, y, i, steps+1);
		on_neighbour(x, y+1, i, steps+1);
		on_neighbour(x, y-1, i, steps+1);
		print_map();
	}
	while (1) {
		i = stack[i].parent;
		x = stack[i].x;
		y = stack[i].y;
		map[y][x] = PATH;
		print_map();
		if (i == -1) {
			break;
		}
		result++;
	}
	printf("%d\n", result);
	return result != 248;
}
