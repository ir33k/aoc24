#include <stdio.h>
#include <stdlib.h>

typedef int levels_t[256];

int
next(char **bp)
{
	int result = -1;
	if (**bp == 0) {
		return result;
	}
	result = atoi(*bp);
	while (**bp  > ' ') (*bp) += 1;	// Skip non white space
	(*bp) += 1;	// Skip white space
	return result;
}

levels_t *
get_levels(char *bp)
{
	static levels_t levels;
	unsigned i;
	for (i=0; ; i++) {
		levels[i] = next(&bp);
		if (levels[i] == -1) break;
	}
	return &levels;
}

int
is_safe(levels_t *levels)
{
	int ignore, i, a, b, increase, diff;
	for (ignore = 0; (*levels)[ignore] != -1; ignore++) {
		i = 0;
		if (i == ignore) i++;
		a = (*levels)[i++];
		if (i == ignore) i++;
		b = (*levels)[i++];
		increase = a < b;
		while (1) {
			if ((a < b) != increase) {
				goto skip;
			}
			diff = a - b;
			if (diff < 0) {
				diff = -diff;
			}
			if (diff < 1 || diff > 3) {
				goto skip;
			}
			a = b;
			if (i == ignore) i++;
			if ((*levels)[i] == -1) break;
			b = (*levels)[i++];
		}
		return 1;
skip:
		continue;
	}
	return 0;
}

int
main(void)
{
	char buf[4096];
	unsigned result;
	levels_t *levels;
	result = 0;
	while (fgets(buf, sizeof(buf), stdin)) {
		levels = get_levels(buf);
		result += is_safe(levels);
	}
	printf("%u\n", result);
	return 0;
}
