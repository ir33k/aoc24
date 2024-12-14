#include <stdio.h>

#define MOD(a,b) (((a) % (b) + (b)) % (b))

int main(void) {
	int i;
	int px,py, vx,vy;	// Robot position and velocity
	int w,h, mx,my;		// Space size and middle line
	unsigned square[4]={0};
	char buf[4096];
	// NOTE(irek): I stored width and height information in input.
	fgets(buf, sizeof buf, stdin);
	sscanf(buf, "w=%d h=%d", &w, &h);
	mx = w/2;
	my = h/2;
	for (i=0; fgets(buf, sizeof buf, stdin); i++) {
		sscanf(buf, "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
		px = MOD(px + vx*100, w);
		py = MOD(py + vy*100, h);
		square[0] += px<mx && py<my;	// Top left
		square[1] += px>mx && py<my;	// Top right
		square[2] += px>mx && py>my;	// Bottom right
		square[3] += px<mx && py>my;	// Bottom left
	}
	printf("%u\n", square[0] * square[1] * square[2] * square[3]);
	return 0;
}
