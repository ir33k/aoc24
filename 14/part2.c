#include <stdio.h>

#define MOD(a,b) (((a) % (b) + (b)) % (b))

struct robot {
	int px,py;	// Position
	int vx,vy;	// Velocity
};

static struct robot robots[512];
static int rcount=0;

int main(void) {
	int usleep(unsigned);
	int i, w,h, x,y, n;
	char buf[4096];
	long unsigned j=0;
	// NOTE(irek): I added width and height information to input files
	// on the first line as example and puzzle input have different
	// width and height which normally had to be hardcoded.
	fgets(buf, sizeof buf, stdin);
	sscanf(buf, "w=%d h=%d", &w, &h);
	while (fgets(buf, sizeof buf, stdin)) {
		sscanf(buf, "p=%d,%d v=%d,%d",
		       &robots[rcount].px, &robots[rcount].py,
		       &robots[rcount].vx, &robots[rcount].vy);
		rcount++;
	}
	y=0;
	for (j=0; j<8258; j++) {
		for (i=0; i<rcount; i++) {
			robots[i].px = MOD(robots[i].px + robots[i].vx, w);
			robots[i].py = MOD(robots[i].py + robots[i].vy, h);
		}
		// Visualisation
		// 8257
		if (j<8257) {
			continue;	
		}
		/**
		 * Esc    - Escape code (0x1B)
		 * Esc[H  - Cursor Home
		 * Esc[2J - Erase Screen
		 */
		fputs("\x1B[H" "\x1B[2J\n", stdout);
		fflush(stdout);
		printf("%lu ------------------------------------\n", j);
		for (y=0; y<h; y++) {
			for (x=0; x<w; x++) {
				n=0;
				for (i=0; i<rcount; i++) {
					n += robots[i].px == x && robots[i].py == y;
				}
				printf("%s", n ? "dP" : "  ");
			}
			printf("\n");
		}
		printf("\n");
		usleep(1000000/16);	// 4 FPS
	// 	for (y=0; y<h; y++) {
	// 		n=0;
	// 		for (x=0; x<w; x++) {
	// 			for (i=0; i<rcount; i++) {
	// 				n += robots[i].p.x == x && robots[i].p.y == y;
	// 			}
	// 		}
	// 		if (n != y*2+1) {
	// 			goto skip;
	// 		}
	// 	}
	// 	break;
	// skip:
	// 	continue;
	}
	printf("%lu\n", j+1);
	return 0;
}
