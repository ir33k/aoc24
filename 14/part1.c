#include <stdio.h>

#define MOD(a,b) (((a) % (b) + (b)) % (b))

struct robot {
	int px,py;	// Position
	int vx,vy;	// Velocity
};

static struct robot robots[512];
static int rcount=0;

static unsigned count(int from_x, int from_y, int to_x, int to_y) {
	int x,y,i,n=0;
	for (y=from_y; y<to_y; y++)
	for (x=from_x; x<to_x; x++)
	for (i=0; i<rcount; i++) {
		n += robots[i].px == x && robots[i].py == y;
	}
	return n;
}

int main(void) {
	int i, w,h;
	int mx,my;	// Middle line
	char buf[4096];
	long unsigned result;
	// NOTE(irek): I added width and height information to input files
	// on the first line as example and puzzle input have different
	// width and height which normally had to be hardcoded.
	fgets(buf, sizeof buf, stdin);
	sscanf(buf, "w=%d h=%d", &w, &h);
	mx = w/2;
	my = h/2;
	while (fgets(buf, sizeof buf, stdin)) {
		sscanf(buf, "p=%d,%d v=%d,%d",
		       &robots[rcount].px, &robots[rcount].py,
		       &robots[rcount].vx, &robots[rcount].vy);
		rcount++;
	}
	for (i=0; i<rcount; i++) {
		robots[i].px = MOD(robots[i].px + robots[i].vx*100, w);
		robots[i].py = MOD(robots[i].py + robots[i].vy*100, h);
	}
	result  = count(0,    0,    mx, my);	// Top left
	result *= count(mx+1, 0,    w,  my);	// Top right
	result *= count(mx+1, my+1, w,  h);	// Bottom right
	result *= count(0,    my+1, mx, h);	// Bottom left
	printf("%lu\n", result);
	return 0;
}
