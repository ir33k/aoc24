#include <stdio.h>
#include <string.h>

// [c0][c1][c2][c3] are a 4 changes in prices that together form an
// unique index to accumulated alues in those arrays:
static unsigned map[20][20][20][20]={0};	// Single buyer prices
static unsigned sum[20][20][20][20]={0};	// Sum of prices

int main(void) {
	int i;
	unsigned secret, price, change, result=0;
	unsigned c0=0, c1=0, c2=0, c3=0;	// 4 changes
	while (scanf("%d\n", &i) > 0) {
		secret = i;
		price = 0;
		memset(map, 0, sizeof map);
		for (i=0; i<2000; i++) {
			// NOTE(irek): +9 to avoid negative numbers
			// because change value is used as index.
			change = (secret % 10 - price) +9;
			price = secret % 10;
			secret ^= (secret * 64)   % 16777216;
			secret ^= (secret / 32)   % 16777216;
			secret ^= (secret * 2048) % 16777216;
			switch (i) {
			case 0: c1 = change; continue;
			case 1: c2 = change; continue;
			case 2: c3 = change; continue;
			}
			c0 = c1;
			c1 = c2;
			c2 = c3;
			c3 = change;
			if (map[c0][c1][c2][c3]) {
				continue;
			}
			map[c0][c1][c2][c3] = price;
			sum[c0][c1][c2][c3] += price;
			if (sum[c0][c1][c2][c3] > result) {
				result = sum[c0][c1][c2][c3];
			}
		}
	}
	printf("%u\n", result);
	return !(result == 23 || result == 1490);
}
