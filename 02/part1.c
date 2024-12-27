#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i, list[8], li, increasing, distance, result=0;
	char buf[256];
	while (fgets(buf, sizeof(buf), stdin)) {
		for (i=0, li=0; buf[i]; li++) {
			list[li] = atoi(buf+i);
			while (buf[i++] > ' ' );
		}
		increasing = list[0] < list[1];
		for (i=1; i<li; i++) {
			distance = list[i-1] - list[i];
			if (distance < 0) distance = -distance;
			if ((list[i-1] < list[i]) != increasing ||
			    distance < 1 || distance > 3) {
				break;
			}
		};
		result += i == li;
	}
	printf("%u\n", result);
	return result != 598;
}
