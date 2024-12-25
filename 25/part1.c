#include <stdio.h>
#define SIZE 5	// Key and lock height and width

int main(void) {
	int locks[512][SIZE]={0}, li=0;
	int  keys[512][SIZE]={0}, ki=0;
	int i,j,k, *array, result=0;
	char buf[8];
	do {
		fgets(buf, sizeof buf, stdin);
		array = buf[0] == '#' ? locks[li++] : keys[ki++];
		for (i=0; i<SIZE; i++) {
			fgets(buf, sizeof buf, stdin);
			for (j=0; j<SIZE; j++) {
				array[j] += buf[j] == '#';
			}
		}
		fgets(buf, sizeof buf, stdin);
	} while (fgets(buf, sizeof buf, stdin));
	for (i=0; i<li; i++)
	for (j=0; j<ki; j++) {
		for (k=0; k<SIZE; k++) {
			if (locks[i][k] + keys[j][k] > SIZE) {
				break;
			}
		}
		result += k == SIZE;
	}
	printf("%d\n", result);
	return !(result == 3327);
}
