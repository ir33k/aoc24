#include <stdio.h>

int main(void) {
	int i;
	long unsigned secret, result=0;
	while (scanf("%d\n", &i) > 0) {
		secret = i;
		for (i=0; i<2000; i++) {
			secret ^= (secret * 64)   % 16777216;
			secret ^= (secret / 32)   % 16777216;
			secret ^= (secret * 2048) % 16777216;
		}
		result += secret;
	}
	printf("%lu\n", result);
	return !(result == 37327623 || result == 13234715490);
}
