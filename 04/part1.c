#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PHRASE "XMAS"

static char *buf;
static int w,h, x,y, len;

void
get_stdin(void)
{
	ssize_t ssz;
	const size_t sz = 32*1024;	// 32 KB should be enough for everyon, right? ^-^
	if (!(buf = malloc(sz))) {
		err(1, 0);
	}
	ssz = read(STDIN_FILENO, buf, sz);
	if (ssz >= (ssize_t)sz) {
		errx(1, "read");
	}
	buf[ssz] = 0;
}

int
check(int dx, int dy)
{
	int i;
	for (i=0; i<len; i++) {
		if (x+dx >= w || x+dx < 0 ||
		    y+dy >= h || y+dy < 0 ||
		    buf[(y+i*dy)*(w+1)+(x+i*dx)] != PHRASE[i]) {
			return 0;
		}
	}
	return 1;
}

int
main(void)
{
	unsigned result;
	get_stdin();
	for (w=0; buf[w] != '\n'; w++);	// Calculate width
	h = strlen(buf) / w -1;	// Calculate height
	result = 0;
	len = strlen(PHRASE);
	for (y=0; y<h; y++)
	for (x=0; x<w; x++) {
		result += check(+1,  0);
		result += check(-1,  0);
		result += check( 0, +1);
		result += check( 0, -1);
		result += check(+1, +1);
		result += check(-1, -1);
		result += check(+1, -1);
		result += check(-1, +1);
	}
	printf("%u\n", result);
	return 0;
}
