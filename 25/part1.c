#include <stdio.h>

static int locks[512][5];
static int li=0;
static int keys[512][5];
static int ki=0;

int main(void) {
	int i,j,k, is_lock, *array;
	char buf[8];
	long unsigned result;
	while (1) {
		fgets(buf, sizeof buf, stdin);
		is_lock = buf[0] == '#';
		array = is_lock ? locks[li] : keys[ki];
		i = is_lock ? 6 : 5;
		for (; i; i--) {
			fgets(buf, sizeof buf, stdin);
			for (j=0; j<5; j++) {
				array[j] += buf[j] == '#';
			}
		}
		if (is_lock) {
			li++;
		} else {
			ki++;
			fgets(buf, sizeof buf, stdin);
		}
		if (!fgets(buf, sizeof buf, stdin)) {
			break;
		}
	}
	result = 0;
	for (i=0; i<li; i++)
	for (j=0; j<ki; j++) {
		for (k=0; k<5; k++) {
			if (locks[i][k] + keys[j][k] > 5) {
				break;
			}
		}
		result += k == 5;
	}
	printf("%lu\n", result);
	return !(result == 3327);
}
