#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <regex.h>

#define PHRASE "XMAS"

char *
get_stdin(void)
{
	static char *buf;
	const size_t siz = 32*1024;	// 32 KB should be enough for everyon, right? ^-^
	if (!(buf = malloc(siz))) {
		err(1, 0);
	}
	if (read(STDIN_FILENO, buf, siz) >= (ssize_t)siz) {
		errx(1, "read");
	}
	return buf;
}

int
main(void)
{
	char *buf;
	int w,h, x,y, i,len, result;
	buf = get_stdin();
	for (w=0; buf[w] != '\n'; w++);	// Calculate width
	h = strlen(buf) / w -1;	// Calculate height
	result = 0;
	len = strlen(PHRASE);
	// From left to right
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			for (i=0; i<len; i++) {
				if (x+i >= w || buf[y*(w+1)+x+i] != PHRASE[i]) {
					goto skip1;
				}
			}
			result++;
		skip1:
			continue;
		}
	}
	// From right to left
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			for (i=0; i<len; i++) {
				if (x-i < 0 || buf[y*(w+1)+x-i] != PHRASE[i]) {
					goto skip2;
				}
			}
			result++;
		skip2:
			continue;
		}
	}
	// From up to down
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			for (i=0; i<len; i++) {
				if (y+i >= h || buf[(y+i)*(w+1)+x] != PHRASE[i]) {
					goto skip3;
				}
			}
			result++;
		skip3:
			continue;
		}
	}
	// From down to up
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			for (i=0; i<len; i++) {
				if (y-i < 0 || buf[(y-i)*(w+1)+x] != PHRASE[i]) {
					goto skip4;
				}
			}
			result++;
		skip4:
			continue;
		}
	}
	// From top left to bottom right
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			for (i=0; i<len; i++) {
				if (x+i >= w || y+i >= h || buf[(y+i)*(w+1)+x+i] != PHRASE[i]) {
					goto skip5;
				}
			}
			result++;
		skip5:
			continue;
		}
	}
	// From top right to bottom left
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			for (i=0; i<len; i++) {
				if (x-i < 0 || y+i >= h || buf[(y+i)*(w+1)+x-i] != PHRASE[i]) {
					goto skip6;
				}
			}
			result++;
		skip6:
			continue;
		}
	}
	// From bottom left to top right
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			for (i=0; i<len; i++) {
				if (x+i >= w || y-i < 0 || buf[(y-i)*(w+1)+x+i] != PHRASE[i]) {
					goto skip7;
				}
			}
			result++;
		skip7:
			continue;
		}
	}
	// From bottom right to top left
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			for (i=0; i<len; i++) {
				if (x-i < 0 || y-i < 0 || buf[(y-i)*(w+1)+x-i] != PHRASE[i]) {
					goto skip8;
				}
			}
			result++;
		skip8:
			continue;
		}
	}
	printf("%u\n", result);
	return 0;
}
