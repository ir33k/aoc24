#include <stdio.h>
#include <string.h>
#include <limits.h>

enum {
	// Map        Directions
	EMPTY = '.',  NORTH = '^',
	WALL  = '#',  EAST  = '>',
	START = 'S',  SAUTH = 'v',
	END   = 'E',  WEST  = '<',
	MARK  = 'O',
};

static char map[256][256];
static int scores[256][256];
static int w=0,h=0;

static void walk(int x, int y, int dir, int score) {
	if (map[y][x] == WALL) {
		return;
	}
	if (scores[y][x] > score) {
		scores[y][x] = score;
	} else if (scores[y][x] < score) {
		return;
	}
	if (map[y][x] == END) {
		return;
	}
	switch (dir) {
	case NORTH:
		walk(x  , y-1, NORTH, score+1);
		walk(x+1, y  , EAST,  score+1001);
		walk(x-1, y  , WEST,  score+1001);
		break;
	case EAST:
		walk(x+1, y  , EAST,  score+1);
		walk(x  , y-1, NORTH, score+1001);
		walk(x  , y+1, SAUTH, score+1001);
		break;
	case SAUTH:
		walk(x  , y+1, SAUTH, score+1);
		walk(x+1, y  , EAST,  score+1001);
		walk(x-1, y  , WEST,  score+1001);
		break;
	case WEST:
		walk(x-1, y  , WEST,  score+1);
		walk(x  , y-1, NORTH, score+1001);
		walk(x  , y+1, SAUTH, score+1001);
		break;
	}
}

static int is_intersection(int x, int y, int dir) {
	switch (dir) {
	case NORTH:
	case SAUTH:
		return map[y][x-1] != WALL || map[y][x+1] != WALL;
	case EAST:
	case WEST:
		return map[y-1][x] != WALL || map[y+1][x] != WALL;
	}
	return 0;
}

static int mark(int x, int y, int dir, int score, int expected_score) {
	int end=0;
	switch (map[y][x]) {
	case WALL: return 0;
	case END:  return expected_score == score;
	}
	if (!is_intersection(x, y, dir) && scores[y][x] != score) {
		return 0;
	}
	switch (dir) {
	case NORTH:
		end += mark(x  , y-1, NORTH, score+1, expected_score);
		end += mark(x+1, y  , EAST,  score+1001, expected_score);
		end += mark(x-1, y  , WEST,  score+1001, expected_score);
		break;
	case EAST:
		end += mark(x+1, y  , EAST,  score+1, expected_score);
		end += mark(x  , y-1, NORTH, score+1001, expected_score);
		end += mark(x  , y+1, SAUTH, score+1001, expected_score);
		break;
	case SAUTH:
		end += mark(x  , y+1, SAUTH, score+1, expected_score);
		end += mark(x+1, y  , EAST,  score+1001, expected_score);
		end += mark(x-1, y  , WEST,  score+1001, expected_score);
		break;
	case WEST:
		end += mark(x-1, y  , WEST,  score+1, expected_score);
		end += mark(x  , y-1, NORTH, score+1001, expected_score);
		end += mark(x  , y+1, SAUTH, score+1001, expected_score);
		break;
	}
	if (end) {
		map[y][x] = MARK;
	}
	return end;
}

int main(void) {
	int x=0,y=0, sx=0,sy=0, result=0, smallest;
	// Load map, set height and width
	while (fgets(map[h], sizeof map[0], stdin)) h++;
	while (*map[w++]);
	// Find start
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		scores[y][x] = INT_MAX;
		if (map[y][x] == START) { sx=x; sy=y; }
	}
	x=sx;
	y=sy;
	walk(x+1, y  , EAST,  1);
	walk(x  , y-1, NORTH, 1001);
	walk(x  , y+1, SAUTH, 1001);
	smallest = scores[1][w-3];
	printf("%d\n", smallest);
	x=sx;
	y=sy;
	mark(x+1, y  , EAST, 1, smallest);
	mark(x  , y-1, NORTH, 1001, smallest);
	mark(x  , y+1, SAUTH, 1001, smallest);
	/* for (y=0; y<h; y++) { */
	/* 	for (x=0; x<w; x++) { */
	/* 		if (scores[y][x] == INT_MAX) { */
	/* 			if (map[y][x] == WALL) { */
	/* 				printf("     "); */
	/* 			} else { */
	/* 				printf(".... "); */
	/* 			} */
	/* 		} else { */
	/* 			if (scores[y][x] >= 10000) { */
	/* 				printf("%.4d ", 9999); */
	/* 			} else { */
	/* 				printf("%.4d ", scores[y][x]); */
	/* 			} */
	/* 		} */
	/* 	} */
	/* 	printf("\n"); */
	/* } */
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			/* printf("%c", map[y][x]); */
			switch (map[y][x]) {
			case START:
			case END:
			case MARK:
				result++;
			}
		}

	}
	/* 522 too low */
	/* 533 right answer for someone else */
	/* 535 right answer for someone else */
	/* 538 */
	/* 563 */
	/* 566 */
	/* 596 */
	/* 639 too high */
	printf("%d\n", result);
	return 0;
}
