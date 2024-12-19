#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://en.wikipedia.org/wiki/Rope_(data_structure)
struct node {
	struct node *next[5];	// We have only 5 indexes (colors)
	int end;
};
static struct node rope_head;

static const int indexof[] = { ['w']=0, ['u']=1, ['b']=2, ['r']=3, ['g']=4 };
static long unsigned cache[64];

static void rope_push(char *c) {
	int i;
	struct node *node = &rope_head;
	for (; *c; c++) {
		i = indexof[(int)*c];
		if (!node->next[i]) {
			node->next[i] = malloc(sizeof *node);
		}
		node = node->next[i];
	}
	node->end = 1;
}

static int rope_contains(char *c, int len) {
	struct node *node = &rope_head;
	for (; len && *c; c++, len--) {
		node = node->next[indexof[(int)*c]];
		if (!node) {
			return 0;
		}
	}
	return node->end;
}

static int rope_length(char *c) {
	int n=0;
	struct node *node = &rope_head;
	for (; *c; c++, n++) {
		node = node->next[indexof[(int)*c]];
		if (!node) {
			break;
		}
	}
	return n;
}

static long unsigned check(char *buf, int n) {
	long unsigned i;
	if (buf[n] == 0) {
		return 1;	// Riched to the end
	}
	if (cache[n]) {		// I have already been here
		return cache[n] - 1;
	}
	cache[n] = 1;		// Mark visited byte with 1
	i = rope_length(buf + n);
	for (; i; i--) {
		if (!rope_contains(buf + n, i)) {
			continue;
		}
		cache[n] += check(buf, n + i);
	}
	return cache[n] -1;
}

int main(void) {
	char buf[4096];
	long unsigned result;
	while (scanf("%[a-z], ", buf) > 0) {
		rope_push(buf);
	}
	result = 0;
	while (scanf("%s\n", buf) > 0) {
		memset(cache, 0, sizeof cache);	// Reset cache
		result += !!check(buf, 0);
	}
	printf("%lu\n", result);
	return result != 344;
}
