#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

struct v2 {
	int x,y;
};

/*
  3       1     tokens
------------------------
N*a.x + M*b.x = prize.x
N*a.y + M*b.y = prize.y
*/
static unsigned count_tokens(struct v2 a, struct v2 b, struct v2 prize) {
	unsigned tokens=-1, cost;
	int n, m, max_n, max_m;
	max_n = MAX(prize.x/a.x, prize.y/a.y);
	max_m = MAX(prize.x/b.x, prize.y/b.y);
	for (n=0; n<max_n; n++)
	for (m=0; m<max_m; m++) {
		if (n*a.x + m*b.x == prize.x &&
		    n*a.y + m*b.y == prize.y) {
			cost = n*3 + m*1;
			if (cost < tokens) {
				tokens = cost;
			}
		}
	}
	return tokens == (unsigned)-1 ? 0 : tokens;
}

int main(void) {
	char buf[4096];
	struct v2 a, b, prize;
	long unsigned result;
	result=0;
	while (1) {
		fgets(buf, sizeof buf, stdin);
		sscanf(buf, "Button A: X+%d, Y+%d", &a.x, &a.y);
		fgets(buf, sizeof buf, stdin);
		sscanf(buf, "Button B: X+%d, Y+%d", &b.x, &b.y);
		fgets(buf, sizeof buf, stdin);
		sscanf(buf, "Prize: X=%d, Y=%d", &prize.x, &prize.y);
		result += count_tokens(a, b, prize);
		if (!fgets(buf, sizeof buf, stdin)) {
			break;
		}
	}
	printf("%lu\n", result);
	return 0;
}
