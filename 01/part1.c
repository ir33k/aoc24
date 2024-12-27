#include <stdio.h>
#include <stdlib.h>

static int compar(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}

int main(void) {
	int i, list[2][1024], result=0;
	for (i=0; scanf("%d %d\n", list[0]+i, list[1]+i) > 0; i++);
	qsort(list[0], i, sizeof(int), &compar);	// Left
	qsort(list[1], i, sizeof(int), &compar);	// Right
	while (i--) result += abs(list[0][i] - list[1][i]);
	printf("%d\n", result);
	return result != 1189304;
}
