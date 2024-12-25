#include <stdio.h>

int main(void) {
	long i,j, list[512]={0}, result=0;
	char buf[8];
	for (i=0; fgets(buf, sizeof buf, stdin); i++) {
		if (buf[0] == '\n') {
			continue;
		}
		for (j=0; j<5; j++) {
			if (buf[j] == '#') {
				list[i/8] |= 1L << ((i%8)+j*7);
			}
		}
	};
	for (i=0;   list[i]; i++)
	for (j=i+1; list[j]; j++) {
		result += !(list[i] & list[j]);
	}
	printf("%ld\n", result);
	return !(result == 3327);
}
