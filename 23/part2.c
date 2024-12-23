#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 0x191A	// Magic number, my secret

/* Convert computer name to single number that is used as index to
 * nodes array and basically for everything.  Working with strings is
 * not optimal.
 *
 * "ta"       Computer name.
 * 0x74 0x61  Each character number in ASCII.
 * 0x13 0x00  Only a-z are used, subtract 'a' to have range from 0 to 25.
 * 0x1300     Combine bytes together into single integer. 
 */
#define INDEXOF(a) (((a)[0] - 'a') << 8) | ((a)[1] - 'a')

struct node {
	int child;
	struct node *next;
};
static struct node *nodes[MAX]={0};	// [parent_index]

static void nodes_add(int parent, int child) {
	struct node *node = nodes[parent];
	if (!node) {
		nodes[parent] = malloc(sizeof *node);	// Let it leak...
		nodes[parent]->child = child;
		nodes[parent]->next = 0;
		return;
	}
	if (node->child == child) {
		return;	// Avoid duplicates
	}
	while (node->next) {
		node = node->next;
		if (node && node->child == child) {
			return;	// Avoid duplicates
		}
	}
	node->next = malloc(sizeof *node); // Memory never bothered me anyway
	node->next->child = child;
	node->next->next = 0;
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

static void node_index_sringify(int index, char *buf) {
	buf[0] = ((index >> 8) & 0x00FF) + 'a';
	buf[1] = ((index >> 0) & 0x00FF) + 'a';
	buf[2] = 0;
}

static int compar(const void *a, const void *b) {
	char left[4], right[4];
	node_index_sringify(*(int*)a, left);
	node_index_sringify(*(int*)b, right);
	return strcmp(left, right);
}

int main(void) {
	char a[4], b[4];
	int i,j,k,next;
	int chain[4096], max[4096];
	int ci, mi=0;
	while (scanf("%[a-z]-%[a-z]\n", a, b) > 0) {
		i = INDEXOF(a);
		j = INDEXOF(b);
		nodes_add(i, j);
		nodes_add(j, i);
	}
	for (i=0; i<MAX; i++) {
		j = 0;
		next = i;
		ci = 0;
		chain[ci++] = next;
		assert((unsigned)ci < (sizeof chain / sizeof chain[0]));
		while (1) {
			next = nodes_get_child_by_index(chain[0], j);
			if (next == -1) {
				break;
			}
			for (k=0; k<ci; k++) {
				if (nodes_child_indexof(next, chain[k]) == -1) {
					break;
				}
			}
			if (k == ci) {
				chain[ci++] = next;
				assert((unsigned)ci < (sizeof chain / sizeof chain[0]));
			}
			j++;
		}
		if (ci > mi) {
			for (j=0; j<ci; j++) {
				max[j] = chain[j];
			}
			mi = ci;
		}
	}
	qsort(max, mi, sizeof max[0], &compar);
	for (i=0; i<mi; i++) {
		node_index_sringify(max[i], a);
		printf("%s,", a);
	}
	printf("\b\n");
	return 0;
}
