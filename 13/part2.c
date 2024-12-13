#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

struct v2 {
	int x,y;
};

static long long unsigned count_tokens(struct v2 a, struct v2 b, struct v2 prize) {
	long double n, m, px,py;
	px = prize.x + 10000000000000;
	py = prize.y + 10000000000000;
	n = (px*b.y - py*b.x) / (a.x*b.y - a.y*b.x);
	m = (py*a.x - px*a.y) / (a.x*b.y - a.y*b.x);
	if ((floorl(n) != n) || (floorl(m) != m)) {
		return 0;	// Can't win this prize
	}
	return 3*n + 1*m;
}

int main(void) {
	char buf[4096];
	struct v2 a, b, prize;
	long long unsigned result;
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
	printf("%llu\n", result);
	return 0;
}
