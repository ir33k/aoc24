#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i,j, list[8], li, tmp[8], increasing, distance, ignore, result=0;
	char buf[256];
	while (fgets(buf, sizeof(buf), stdin)) {
		for (i=0, li=0; buf[i]; li++) {
			list[li] = atoi(buf+i);
			while (buf[i++] > ' ' );
		}
		for (ignore=0; ignore<li; ignore++) {
			for (i=0, j=0; i<li;) {
				if (i == ignore) i++;
				tmp[j++] = list[i++];
			}
			increasing = tmp[0] < tmp[1];
			for (i=1; i<li-1; i++) {
				distance = tmp[i-1] - tmp[i];
				if (distance < 0) distance = -distance;
				if ((tmp[i-1] < tmp[i]) != increasing ||
				    distance < 1 || distance > 3) {
					break;
				}
			};
			if (i == li-1) {
				result++;
				break;
			}
		}
	}
	printf("%u\n", result);
	return result != 634;
}
