#include <stdio.h>
#include <stdlib.h>

int
compar(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

int
main(void)
{
	unsigned i, count;
	char buf[4096];
	int left[1024], right[1024], result;
	for (i=0; fgets(buf, sizeof(buf), stdin); i++) {
		sscanf(buf, "%d %d", &left[i], &right[i]);
	}
	count = i;
	qsort(left,  count, sizeof(int), &compar);
	qsort(right, count, sizeof(int), &compar);
	result = 0;
	for (i=0; i<count; i++) {
		result += abs(left[i] - right[i]);
	}
	printf("%d\n", result);
	return 0;
}
