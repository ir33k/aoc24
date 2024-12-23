#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 0x191A	// Magic number, my secret

/* "ta"       Computer name.
 * 0x74 0x61  Each character number.
 * 0x13 0x00  Only a-z are used, subtract 'a' to have range from 0 to 25.
 * 0x1300     Combine bytes together into single integer. 
 */
#define INDEXOF(a) (((a)[0] - 'a') << 8) | ((a)[1] - 'a')
#define IS_CHIEF(a) (((a) >> 8) == 0x13)

struct node {
	int child;
	struct node *next;
};
static struct node *nodes[MAX]={0};	// [parent_index]
static int connections[4096][3];
static int ci=0;

static void nodes_add(int parent, int child) {
	struct node *node = nodes[parent];
	if (!node) {
		nodes[parent] = malloc(sizeof *node);
		nodes[parent]->child = child;
		nodes[parent]->next = 0;
		return;
	}
	if (node->child == child) {
		return;
	}
	while (node->next) {
		node = node->next;
		if (node && node->child == child) {
			return;
		}
	}
	node->next = malloc(sizeof *node);
	node->next->child = child;
	node->next->next = 0;
}

static int nodes_size(int parent) {
	struct node *node = nodes[parent];
	int n;
	for (n=0; node; n++) node = node->next;
	return n;
}

static int nodes_get_child_by_index(int parent, int n) {
	struct node *node = nodes[parent];
	for (; n && node->next; n--) node = node->next;
	return n == 0 && node ? node->child : -1;
}

static int nodes_child_indexof(int parent, int child) {
	struct node *node = nodes[parent];
	int i;
	for (i=0; node; i++, node=node->next) {
		if (node->child == child) return i;
	}
	return -1;
}

static int connections_has(int connection[3]) {
	int i;
	for (i=0; i<ci; i++) {
		if (connections[i][0] == connection[0] &&
		    connections[i][1] == connection[1] &&
		    connections[i][2] == connection[2]) {
			return 1;
		}
	}
	return 0;
}

static int compar(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}

static void connections_add(int one, int two, int three) {
	int connection[3];
	if (!(IS_CHIEF(one) || IS_CHIEF(two) || IS_CHIEF(three))) {
		return;
	}
	connection[0] = one;
	connection[1] = two;
	connection[2] = three;
	qsort(connection, 3, sizeof(int), &compar);
	if (connections_has(connection)) {
		return;
	}
	connections[ci][0] = connection[0];
	connections[ci][1] = connection[1];
	connections[ci][2] = connection[2];
	ci++;
	assert((unsigned)ci < sizeof connections / sizeof connections[0]);
}

int main(void) {
	char a[4], b[4];
	int i,j,k, n, one, two, three;
	while (scanf("%[a-z]-%[a-z]\n", a, b) > 0) {
		i = INDEXOF(a);
		j = INDEXOF(b);
		nodes_add(i, j);
		nodes_add(j, i);
	}
	for (i=0; i<MAX; i++) {
		n = nodes_size(i);
		if (n == 0) {
			continue;
		}
		one = i;
		for (j=0; j<n; j++) {
			two = nodes_get_child_by_index(one, j);
			if (two == -1) {
				continue;
			}
			if (nodes_child_indexof(two, one) == -1) {
				continue;
			}
			for (k=j+1; k<n; k++) {
				three = nodes_get_child_by_index(one, k);
				if (nodes_child_indexof(three, one) == -1) {
					continue;
				}
				if (nodes_child_indexof(three, two) == -1) {
					continue;
				}
				connections_add(one, two, three);
			}
		}
	}
	printf("%d\n", ci);
	return !(ci == 1119 || ci == 7);
}
