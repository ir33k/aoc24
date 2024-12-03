#include <stdio.h>
#include <stdlib.h>

int
main(void) {
	size_t i,j,k;
	char buf[4096];
	int left, right, appears, result;
	int list[2][1024];	// Left and right lists
	i = 0;
	while (fgets(buf, sizeof(buf), stdin)) {
		sscanf(buf, "%d %d", &left, &right);
		list[0][i] = left;
		list[1][i] = right;
		i++;
	}
	result = 0;
	for (j=0; j<i; j++) {
		appears = 0;
		for (k=0; k<i; k++) {
			if (list[0][j] == list[1][k]) {
				appears++;
			}
		}
		result += list[0][j] * appears;
	}
	printf("%d\n", result);
	return 0;
}
