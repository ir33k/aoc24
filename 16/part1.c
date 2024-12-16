#include <stdio.h>
#include <limits.h>

int usleep(unsigned);

enum {
	// Map        Directions    Turns      
	EMPTY = '.',  NORTH = '^',  FORWARD = 'f',
	WALL  = '#',  EAST  = '>',  RIGHT   = 'r',
	START = 'S',  SAUTH = 'v',  LEFT    = 'l',
	END   = 'E',  WEST  = '<',
};

static char map[256][256];
static int w=0,h=0;

static void print_map() {
	int x,y;
	fputs("\x1B[H" "\x1B[2J", stdout);
	fflush(stdout);
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		switch (map[y][x]) {
		case NORTH:
		case EAST:
		case SAUTH:
		case WEST:
		case FORWARD:
		case RIGHT:
		case LEFT:
			fputs("\x1B[7m", stdout);
			break;
		}
		putchar(map[y][x]);
		fputs("\x1B[0m", stdout);
	}
	fflush(stdout);
}

static int is_intersection(int x, int y, int dir) {
	switch (map[y][x]) {
	case FORWARD:
	case LEFT:
	case RIGHT:
		return 1;
	}
	switch (dir) {
	case SAUTH:
	case NORTH:
		return map[y][x+1] == EMPTY || map[y][x-1] == EMPTY;
	case EAST:
	case WEST:
		return map[y+1][x] == EMPTY || map[y-1][x] == EMPTY;
	}
	return 0;
}

static int can_move_forward(int x, int y, int dir) {
	char next = WALL;
	switch (dir) {
	case NORTH: next = map[y-1][x  ]; break;
	case EAST:  next = map[y  ][x+1]; break;
	case SAUTH: next = map[y+1][x  ]; break;
	case WEST:  next = map[y  ][x-1]; break;
	}
	return next == EMPTY || next == END;
}

static int turn_right(int dir) {
	switch (dir) {
	case EAST:  return SAUTH;
	case SAUTH: return WEST;
	case WEST:  return NORTH;
	case NORTH: return EAST;
	}
	return -1;
}

static int backtrack(int *x, int *y, int dir, int *score) {
	int deadend = 0;
	char replace = EMPTY;
	/* int mx,my; */
	/* for (my=0; my<h; my++) */
	/* for (mx=0; mx<w; mx++) { */
	/* 	putchar(map[my][mx]); */
	/* } */
	switch (dir) {
	case NORTH: deadend = map[(*y)-1][(*x)  ] == WALL; break;
	case EAST:  deadend = map[(*y)  ][(*x)+1] == WALL; break;
	case SAUTH: deadend = map[(*y)+1][(*x)  ] == WALL; break;
	case WEST:  deadend = map[(*y)  ][(*x)-1] == WALL; break;
	}
	if (map[*y][*x] == EMPTY && !is_intersection(*x, *y, dir) && deadend) {
		replace = WALL;
		map[*y][*x] = replace;
	}
	while (1) {
		switch (dir) {
		case EAST:  (*x)--; break;
		case WEST:  (*x)++; break;
		case NORTH: (*y)++; break;
		case SAUTH: (*y)--; break;
		}
		*score -= 1;
		switch (map[*y][*x]) {
		case FORWARD:
		case RIGHT:
		case LEFT:
			return 0;
		case WALL:
			return 1;
		default:
			map[*y][*x] = replace;
		}
	}
	return 1;
}

int main(void) {
	int x=0,y=0, dir=EAST;
	int score, result;
	// Load map, set height and width
	while (fgets(map[h], sizeof map[0], stdin)) h++;
	while (*map[w++]);
	// Find start
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		if (map[y][x] == START) {
			goto found;
		}
	}
found:
	score = 0;
	result = INT_MAX;
	while (1) {
		while (score > 122540 || score > result) {
			switch (map[y][x]) {
			case FORWARD:
				map[y][x] = EMPTY;
				break;
			case LEFT:
				map[y][x] = EMPTY;
				score -= 1000;
				dir = turn_right(dir);
				break;
			case RIGHT:
				map[y][x] = EMPTY;
				score -= 1000;
				dir = turn_right(dir);
				dir = turn_right(dir);
				dir = turn_right(dir);
				break;
			}
			if (backtrack(&x, &y, dir, &score)) {
				goto end;
			}
		}
		/* printf("Score: %d / %d\n", score, result); */
		if (is_intersection(x, y, dir)) {
		turn:
			switch (map[y][x]) {
			case START:
			case EMPTY:
				map[y][x] = FORWARD;
				if (!can_move_forward(x, y, dir)) {
					goto turn;
				}
				break;
			case FORWARD:
				map[y][x] = RIGHT;
				dir = turn_right(dir);
				score += 1000;
				if (!can_move_forward(x, y, dir)) {
					goto turn;
				}
				break;
			case RIGHT:
				map[y][x] = LEFT;
				dir = turn_right(dir);
				dir = turn_right(dir);
				if (!can_move_forward(x, y, dir)) {
					goto turn;
				}
				break;
			case LEFT:
				map[y][x] = EMPTY;
				dir = turn_right(dir);
				score -= 1000;
				if (backtrack(&x, &y, dir, &score)) {
					goto end;
				}
				/* print_map(); */
				/* printf("Score: %d\n", score); */
				/* usleep(1000000/200); */
				continue;
			}
		}
		if (!can_move_forward(x, y, dir)) {
			if (backtrack(&x, &y, dir, &score)) {
				break;
			}
			continue;
		}
		if (map[y][x] == EMPTY) {
			map[y][x] = dir;
		}
		switch (dir) {
		case EAST:  x++; break;
		case SAUTH: y++; break;
		case WEST:  x--; break;
		case NORTH: y--; break;
		}
		score++;
		if (map[y][x] != END) {
			continue;
		}
		if (score < result) {
			printf("Score %d\n", score);
			result = score;
		}
		if (backtrack(&x, &y, dir, &score)) {
			break;
		}
	}
end:
	// 130560 too high
	printf("%d\n", result);
	return 0;
}
