#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int indexof[] = {
	['w'] = 0,
	['u'] = 1,
	['b'] = 2,
	['r'] = 3,
	['g'] = 4,
};

struct node {
	struct node *next[5];
	int end;
};
static struct node head;

static long unsigned visited[64];

static void rope_push(char *c) {
	int i;
	struct node *node = &head;
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
	struct node *node = &head;
	for (; len && *c; c++, len--) {
		assert(*c);
		node = node->next[indexof[(int)*c]];
		if (!node) {
			return 0;
		}
	}
	return node->end;
}

static int rope_length(char *c) {
	int n=0;
	struct node *node = &head;
	for (; *c; c++) {
		node = node->next[indexof[(int)*c]];
		if (!node) {
			break;
		}
		n++;
	}
	return n;
}

static long unsigned check(char *buf, int skip) {
	int i;
	if (buf[skip] == 0) {
		return 1;	// Riched to the end
	}
	if (visited[skip]) {
		return 0;
	}
	visited[skip] = 1;
	i = rope_length(buf + skip);
	for (; i; i--) {
		if (!rope_contains(buf + skip, i)) {
			continue;
		}
		if (check(buf, skip + i)) {
			return 1;
		}
	}
	return 0;
}

int main(void) {
	char buf[4096];
	long unsigned result;
	while (scanf("%[a-z], ", buf) > 0) {
		rope_push(buf);
	}
	result = 0;
	while (scanf("%s\n", buf) > 0) {
		memset(visited, 0, sizeof visited);
		result += check(buf, 0);
	}
	printf("%lu\n", result);
	return result != 344;
}
