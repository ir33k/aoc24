#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	char buf[4096];
	unsigned i, j, n, count, result;
	int left[1024], right[1024];
	for (i=0; fgets(buf, sizeof(buf), stdin); i++) {
		sscanf(buf, "%d %d", &left[i], &right[i]);
	}
	count = i;
	result = 0;
	for (i=0; i<count; i++) {
		for (n=0, j=0; j<count; j++) {
			n += left[i] == right[j];
		}
		result += left[i] * n;
	}
	printf("%d\n", result);
	return 0;
}
