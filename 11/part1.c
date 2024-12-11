#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4096	// Maxinum number of different stones

static long unsigned stones[MAX];
static long unsigned stones_count[2][MAX]={0};	// [2] for current and next turn
static unsigned stones_length=0;

static void update(long unsigned stone, int turn, long unsigned count) {
	unsigned i;
	for (i=0; i < stones_length && stones[i] != stone; i++);
	if (i == stones_length) {	// Stone not found, add new stone
		assert(i < MAX);
		stones[stones_length++] = stone;
	}
	stones_count[turn][i] += count;
}

int main(void) {
	char buf[4096];
	unsigned i, length, blink, turn;
	unsigned long count, left, right, result;
	fgets(buf, sizeof buf, stdin);
	turn=0;
	for (i=0; buf[i]; i++) {
		stones[stones_length] = atoi(buf+i);
		stones_count[turn][stones_length++] = 1;
		while (buf[i] > ' ') i++;
	}
	for (blink=0; blink<25; blink++) {
		for (i=0; i<stones_length; i++) {
			count = stones_count[turn][i];
			if (count == 0) {
				continue;
			}
			// Rule 1
			if (stones[i] == 0) {
				update(1, !turn, count);
				continue;
			}
			// Rule 2
			length = sprintf(buf, "%lu", stones[i]);
			if ((length % 2) == 0) {
				right = atoi(buf+(length/2));
				buf[length/2] = 0;
				left = atoi(buf);
				update(left, !turn, count);
				update(right, !turn, count);
				continue;
			}
			// Rule 3
			update(stones[i]*2024, !turn, count);
		}
		memset(stones_count[turn], 0, sizeof stones_count[0]);
		turn = !turn;
	}
	result = 0;
	for (i=0; i<stones_length; i++) {
		result += stones_count[turn][i];
	}
	printf("%lu\n", result);
	return 0;
}
