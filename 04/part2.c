#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *buf;

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
main(void)
{
	unsigned result;
	int w,h, x,y;
	get_stdin();
	for (w=0; buf[w] != '\n'; w++);	// Calculate width
	h = strlen(buf) / w -1;	// Calculate height
	result = 0;
	for (y=1; y<h-1; y++)
	for (x=1; x<w-1; x++) {
		result +=
			buf[y*(w+1)+x] == 'A' &&
			((buf[(y-1)*(w+1)+(x-1)] == 'M' && buf[(y+1)*(w+1)+(x+1)] == 'S') ||
			 (buf[(y-1)*(w+1)+(x-1)] == 'S' && buf[(y+1)*(w+1)+(x+1)] == 'M')) &&
			((buf[(y-1)*(w+1)+(x+1)] == 'M' && buf[(y+1)*(w+1)+(x-1)] == 'S') ||
			 (buf[(y-1)*(w+1)+(x+1)] == 'S' && buf[(y+1)*(w+1)+(x-1)] == 'M'));
	}
	printf("%u\n", result);
	return 0;
}
