#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum { X=0, Y=1 };

static int rules[2048][2];
static int rules_count;
static int update[1024];
static int update_count;
static int sorted[1024];

static int
compar(const void *tmp_a, const void *tmp_b)
{
	int i, a, b;
	a = *(int*)tmp_a;
	b = *(int*)tmp_b;
	for (i=0; i < rules_count; i++) {
		if (a == rules[i][X] &&
		    b == rules[i][Y]) {
			return -1;
		}
		if (b == rules[i][X] &&
		    a == rules[i][Y]) {
			return 1;
		}
	}
	return 0;
}

int
main(void)
{
	char buf[4096];
	int i,j, is_different;
	unsigned result;
	result = 0;
	// Collect rules
	for (i=0; fgets(buf, sizeof buf, stdin) && buf[0] != '\n'; i++) {
		sscanf(buf, "%d|%d", &rules[i][X], &rules[i][Y]);
	}
	rules_count = i;
	// Go over each update
	while (fgets(buf, sizeof buf, stdin)) {
		// Parse update line
		for (i=0, j=0; buf[i]; i += 3, j++) {
			update[j] = atoi(buf + i);
			sorted[j] = atoi(buf + i);
		}
		update_count = j;
		qsort(sorted, update_count, sizeof sorted[0], compar);
		is_different = 0;
		for (i=0; i<update_count; i++) {
			if (update[i] != sorted[i]) {
				is_different = 1;
				break;
			}
		}
		if (!is_different) {
			result += update[update_count / 2];
		}
	}
	printf("%u\n", result);
	return 0;
}
