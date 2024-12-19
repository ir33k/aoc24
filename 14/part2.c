#include <stdio.h>
#define MOD(a,b) (((a) % (b) + (b)) % (b))

struct robot {
	int px,py;	// Position
	int vx,vy;	// Velocity
};

static struct robot robots[512];
static int rcount=0;

// def estimate_noise(I):
// 
//   H, W = I.shape
//   M = [[ 1, -2,  1],
//        [-2,  4, -2],
//        [ 1, -2,  1]]
//   sigma = np.sum(np.sum(np.absolute(convolve2d(I, M))))
//   sigma = sigma * math.sqrt(0.5 * math.pi) / (6 * (W-2) * (H-2))
//   return sigma
static float noise_level(void) {
}

int main(void) {
	int usleep(unsigned);
	int i, w,h, x,y, n;
	char buf[4096];
	long unsigned j=0;
	scanf("w=%d h=%d\n", &w, &h);	// NOTE(irek): I stored size in input.
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
		usleep(1000000/16);	// 16 FPS
	}
	printf("%lu\n", j+1);
	return 0;
}
