#include <stdio.h>
#include <stdlib.h>

#define ABS(x) ((x) < 0 ? -(x) : (x))

int compar(const void *a, const void *b)
{
	return (*(int*)a) - (*(int*)b);
}

int
main(void) {
	size_t i,j;
	char buf[4096];
	int left, right, distance;
	int list[2][1024];	// Left and right lists
	i = 0;
	while (fgets(buf, sizeof(buf), stdin)) {
		sscanf(buf, "%d %d", &left, &right);
		list[0][i] = left;
		list[1][i] = right;
		i++;
	}
	qsort(list[0], i, sizeof(int), &compar);
	qsort(list[1], i, sizeof(int), &compar);
	distance = 0;
	for (j=0; j<i; j++) {
		distance += ABS(list[0][j] - list[1][j]);
	}
	printf("%d\n", distance);
	return 0;
}
