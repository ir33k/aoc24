#include <stdio.h>
#define MOD(a,b) (((a) % (b) + (b)) % (b))

int main(void) {
	int w,h, x,y, vx,vy, square[4]={0};
	scanf("w=%d h=%d\n", &w, &h);	// NOTE(irek): I stored size in input.
	while (scanf("p=%d,%d v=%d,%d\n", &x, &y, &vx, &vy) != EOF) {
		x = MOD(x + vx*100, w);
		y = MOD(y + vy*100, h);
		square[x/(w/2+1) + y/(h/2+1)*2] += x != w/2 && y != h/2;
	}
	printf("%d\n", square[0] * square[1] * square[2] * square[3]);
	return 0;
}
