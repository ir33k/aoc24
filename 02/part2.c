#include <stdio.h>
#include <stdlib.h>

typedef int levels_t[256];

int
next(char **bp)
{
	int a;
	if (**bp == 0) {
		return -1;
	}
	a = atoi(*bp);
	while (**bp > ' ') (*bp) += 1;
	(*bp) += 1;
	return a;
}

levels_t *
get_levels(char *bp)
{
	static levels_t levels;
	int i;
	i = 0;
	while (1) {
		levels[i] = next(&bp);
		if (levels[i] == -1) {
			break;
		}
		i++;
	}
	return &levels;
}

int
is_safe(levels_t *levels)
{
	int ignore;
	int i, a, b;
	int increase, diff;
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
	}
	return 0;
}

int
main(void) {
	char buf[4096];
	unsigned safe;
	levels_t *levels;
	safe = 0;
	while (fgets(buf, sizeof(buf), stdin)) {
		levels = get_levels(buf);
		safe += is_safe(levels);
	}
	printf("%u\n", safe);
	return 0;
}
