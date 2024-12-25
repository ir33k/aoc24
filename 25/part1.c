#include <stdio.h>
#define SIZE 5	// Key and lock height and width

int main(void) {
	int locks[512]={0}, li=0;
	int  keys[512]={0}, ki=0;
	int i,j, *tmp, result=0;
	char buf[8];
	do {
		fgets(buf, sizeof buf, stdin);
		tmp = buf[0] == '#' ? &locks[li++] : &keys[ki++];
		for (i=0; i<SIZE; i++) {
			fgets(buf, sizeof buf, stdin);
			for (j=0; j<SIZE; j++) {
				if (buf[j] == '#') {
					*tmp |= 1 << (i+j*SIZE);
				}
			}
		}
		fgets(buf, sizeof buf, stdin);
	} while (fgets(buf, sizeof buf, stdin));
	for (i=0; i<li; i++)
	for (j=0; j<ki; j++) {
		result += !(locks[i] & keys[j]);
	}
	printf("%d\n", result);
	return !(result == 3327);
}
