#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct v2 { int x,y; };

static long long unsigned
count_tokens(struct v2 a, struct v2 b, struct v2 prize)
{
	long double n, m, px,py;
	px = prize.x;
	py = prize.y;
	n = (px*b.y - py*b.x) / (a.x*b.y - a.y*b.x);
	m = (py*a.x - px*a.y) / (a.x*b.y - a.y*b.x);
	return (floorl(n) != n) || (floorl(m) != m) ? 0 : 3*n + 1*m;
}

int main(void) {
	char buf[4096];
	struct v2 a, b, prize;
	long long unsigned result=0;
	do {
		fgets(buf, sizeof buf, stdin);
		sscanf(buf, "Button A: X+%d, Y+%d", &a.x, &a.y);
		fgets(buf, sizeof buf, stdin);
		sscanf(buf, "Button B: X+%d, Y+%d", &b.x, &b.y);
		fgets(buf, sizeof buf, stdin);
		sscanf(buf, "Prize: X=%d, Y=%d", &prize.x, &prize.y);
		result += count_tokens(a, b, prize);
	} while (fgets(buf, sizeof buf, stdin));
	printf("%llu\n", result);
	return 0;
}
