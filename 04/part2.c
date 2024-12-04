#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <regex.h>

#define PHRASE "MAS"

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
	//
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			for (i=0; i<len; i++) {
				if (x+i >= w ||
				    y+i >= h ||
				    buf[(y+i)*(w+1)+(x+i)] != PHRASE[i]) {
					goto skip1;
				}
				if (x+i >= w ||
				    y+len-1-i < 0 ||
				    buf[(y+len-1-i)*(w+1)+(x+i)] != PHRASE[i]) {
					goto skip1;
				}
			}
			result++;
		skip1:
			continue;
		}
	}
	//
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			for (i=0; i<len; i++) {
				if (x+i >= w ||
				    y+i >= h ||
				    buf[(y+i)*(w+1)+(x+i)] != PHRASE[i]) {
					goto skip2;
				}
				if (x+len-1-i < 0 ||
				    y+i >= h ||
				    buf[(y+i)*(w+1)+(x+len-1-i)] != PHRASE[i]) {
					goto skip2;
				}
			}
			result++;
		skip2:
			continue;
		}
	}
	//
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			for (i=0; i<len; i++) {
				if (x+len-1-i < 0 ||
				    y+len-1-i < 0 ||
				    buf[(y+len-1-i)*(w+1)+(x+len-1-i)] != PHRASE[i]) {
					goto skip3;
				}
				if (x+i >= w ||
				    y+len-1-i < 0 ||
				    buf[(y+len-1-i)*(w+1)+(x+i)] != PHRASE[i]) {
					goto skip3;
				}
			}
			result++;
		skip3:
			continue;
		}
	}
	//
	for (y=0; y<h; y++) {
		for (x=0; x<w; x++) {
			for (i=0; i<len; i++) {
				if (x+len-1-i < 0 ||
				    y+len-1-i < 0 ||
				    buf[(y+len-1-i)*(w+1)+(x+len-1-i)] != PHRASE[i]) {
					goto skip4;
				}
				if (x+len-1-i < 0 ||
				    y+i >= h ||
				    buf[(y+i)*(w+1)+(x+len-1-i)] != PHRASE[i]) {
					goto skip4;
				}
			}
			result++;
		skip4:
			continue;
		}
	}
	printf("%u\n", result);
	return 0;
}
