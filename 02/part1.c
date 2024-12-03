#include <stdio.h>
#include <stdlib.h>

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

int
main(void) {
	char buf[4096], *bp;
	int a,b, diff, increase;
	unsigned abs, safe;
	safe = 0;
skip:	while ((bp = fgets(buf, sizeof(buf), stdin))) {
		a = next(&bp);
		b = next(&bp);
		increase = a < b;
		while (1) {
			diff = a - b;
			abs = diff < 0 ? -diff : diff;
			if (a < b != increase || abs < 1 || abs > 3) {
				goto skip;
			}
			a = b;
			b = next(&bp);
			if (b == -1) {
				break;
			}
		}
		safe++;
	}
	printf("%u\n", safe);
	return 0;
}
