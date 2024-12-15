#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <termios.h>

enum {
	EMPTY = '.',
	ROBOT = '@',
	WALL  = '#',
	BOX   = 'O',
	UP    = '^',
	RIGHT = '>',
	DOWN  = 'v',
	LEFT  = '<',
};

static char map[64][64];	// [y][x]
static int w=0,h=0;		// Map size

static void print_map(int robot, int rx, int ry) {
	int x,y;
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		putchar(' ');	// Make map more square
		putchar(map[y][x] == ROBOT ? robot : map[y][x]);
	}
	printf("\x1B[%d;%dH", ry+1, (rx+1)*2);
	fflush(stdout);
}

static int move(int x, int y, int dx, int dy) {
	if (map[y+dy][x+dx] == BOX) {
		move(x+dx, y+dy, dx, dy);
	}
	if (map[y+dy][x+dx] != EMPTY) {
		return 0;
	}
	map[y+dy][x+dx] = map[y][x];
	map[y][x] = EMPTY;
	return 1;
}

static char onchar(void) {
        char c = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0) {
                err(1, "tcgetattr");
	}
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0) {
                err(1, "tcsetattr 1");
	}
        if (read(0, &c, 1) < 0) {
                err(1, 0);
	}
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0) {
                err(1, "tcsetattr 2");
	}
        return c;
}

static void clear_screen(void)
{
	/**
	 * Esc    - Escape code (0x1B)
	 * Esc[H  - Cursor Home
	 * Esc[2J - Erase Screen
	 */
	fputs("\x1B[H" "\x1B[2J", stdout);
	fflush(stdout);
}

int main(int argc, char **argv) {
	int x=0,y=0, dx,dy, direction;
	FILE *fp;
	(void)argc;
	if (!(fp = fopen(argv[1], "r"))) {
		err(1, "fopen");
	}
	// Load map, set height and width
	while (fgets(map[h], sizeof map[0], fp) && map[h][0] != '\n') h++;
	while (*map[++w]);
	// Find robot
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		if (map[y][x] == ROBOT) {
			goto found;
		}
	}
found:
	clear_screen();
	print_map(ROBOT, x, y);
	// Move robot
	while (1) {
		direction = 0;
		switch (onchar()) {
		case 'q':
		case 'Q':
			goto end;
		case 0x1B:	// ESC
			if (onchar() != '[') {
				continue;
			}
			// Arrows
			switch (onchar()) {
			case 65: direction = UP;    break;
			case 67: direction = RIGHT; break;
			case 66: direction = DOWN;  break;
			case 68: direction = LEFT;  break;
			}
			break;
		}
		switch (direction) {
		case UP:    dx= 0; dy=-1; break;
		case RIGHT: dx=+1; dy= 0; break;
		case DOWN:  dx= 0; dy=+1; break;
		case LEFT:  dx=-1; dy= 0; break;
		default:
			clear_screen();
			print_map(ROBOT, x, y);
			continue;
		}
		if (move(x, y, dx, dy)) {
			x+=dx;
			y+=dy;
		}
		clear_screen();
		print_map(direction, x, y);
	}
end:
	return 0;
}
