#include <stdio.h>

int main(void) {
	int i,j, list[2][1024], li=0, result=0;
	for (li=0; scanf("%d %d\n", list[0]+li, list[1]+li) > 0; li++);
	for (i=0; i<li; i++)
	for (j=0; j<li; j++) {
		result += list[0][i] * (list[0][i] == list[1][j]);
	}
	printf("%d\n", result);
	return result != 24349736;
}
