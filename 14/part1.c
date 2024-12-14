#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MOD(a,b) (((a) % (b) + (b)) % (b))

struct v2 { int x,y; };
struct robot { struct v2 p,v; };

static int w, h;
static struct robot robots[512];
static int rcount=0;

int main(void) {
	int i,j, x,y, n;
	char buf[4096];
	struct v2 mid;
	long unsigned result;
	// NOTE(irek): I added width and height information to input files
	// on the first line as example and puzzle input have different
	// width and height which normally had to be hardcoded.
	fgets(buf, sizeof buf, stdin);
	sscanf(buf, "w=%d h=%d", &w, &h);
	mid.x = w/2;
	mid.y = h/2;
	while (fgets(buf, sizeof buf, stdin)) {
		sscanf(buf, "p=%d,%d v=%d,%d",
		       &robots[rcount].p.x,
		       &robots[rcount].p.y,
		       &robots[rcount].v.x,
		       &robots[rcount].v.y);
		rcount++;
	}
	for (i=0; i<rcount; i++)
	for (j=0; j<100; j++) {
		robots[i].p.x = MOD(robots[i].p.x + robots[i].v.x, w);
		robots[i].p.y = MOD(robots[i].p.y + robots[i].v.y, h);
	}

	result=1;
	n=0;

	for (y=0; y<mid.y; y++)
	for (x=0; x<mid.x; x++)
	for (i=0; i<rcount; i++) {
		n += robots[i].p.x == x && robots[i].p.y == y;
	}
	result *= n;

	n=0;
	for (y=0; y<mid.y; y++)
	for (x=mid.x+1; x<w; x++)
	for (i=0; i<rcount; i++) {
		n += robots[i].p.x == x && robots[i].p.y == y;
	}
	result *= n;

	n=0;
	for (y=mid.y+1; y<h; y++)
	for (x=mid.x+1; x<w; x++)
	for (i=0; i<rcount; i++) {
		n += robots[i].p.x == x && robots[i].p.y == y;
	}
	result *= n;

	n=0;
	for (y=mid.y+1; y<h; y++)
	for (x=0; x<mid.x; x++)
	for (i=0; i<rcount; i++) {
		n += robots[i].p.x == x && robots[i].p.y == y;
	}
	result *= n;

	printf("%lu\n", result);
	return 0;
}
