#include <assert.h>
#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct stone {
	struct stone *next;	// Linked list <3
	struct stone *prev;
	long unsigned value;
	long unsigned count[76];
};

static struct stone *
find(struct stone *head, long unsigned value)
{
	struct stone *node;
	for (node=head; node; node=node->next) {
		if (node->value == value) {
			return node;
		}
	}
	return 0;
}

int main(void) {
	unsigned i;
	char buf[4096];
	long unsigned result, count;
	long unsigned left, right;
	struct stone *head, *node, *new, *found;
	fgets(buf, sizeof buf, stdin);
	head = malloc(sizeof *head);
	memset(head, 0, sizeof *head);
	node = head;
	node->next = 0;
	node->prev = 0;
	i = 0;
	while (1) {
		node->value = atoi(buf+i);
		// NOTE(irek): In examples and input number do not repeat.
		// So there is no need to accumulate them in single node.
		// Count at the begginig will always be 1.
		node->count[0]++;
		while (buf[i] > ' ') i++;
		if (buf[i] == '\n') break;
		while (buf[i] == ' ') i++;
		new = malloc(sizeof *new);
		memset(new, 0, sizeof *new);
		new->prev = node;
		node->next = new;
		node = node->next;
	}
	for (i=0; i<75; i++) {
		for (node=head; node; node=node->next) {
			if (node->count[i] == 0) {
				continue;
			}
			// Rule 1
			if (node->value == 0) {
				found = find(head, 1);
				if (found) {
					found->count[i+1] = found->count[i+1] + node->count[i];
				} else {
					node->value = 1;
					node->count[i+1] = node->count[i];
				}
				continue;
			}
			// Rule 2
			sprintf(buf, "%lu", node->value);
			count = strlen(buf);
			if ((count % 2) == 0) {
				right = atoi(buf + (count/2));
				buf[count/2] = 0;
				left = atoi(buf);
				//
				found = find(head, left);
				if (found) {
					found->count[i+1] = found->count[i+1] + node->count[i];
				} else {
					new = malloc(sizeof *new);
					memset(new, 0, sizeof *new);
					new->value = left;
					new->count[i+1] += node->count[i];
					new->next = head;
					head->prev = new;
					head = new;
				}
				//
				found = find(head, right);
				if (found) {
					found->count[i+1] = found->count[i+1] + node->count[i];
				} else {
					new = malloc(sizeof *new);
					memset(new, 0, sizeof *new);
					new->value = right;
					new->count[i+1] += node->count[i];
					new->next = head;
					head->prev = new;
					head = new;
				}
				continue;
			}
			// Rule 3
			left = node->value * 2024;
			found = find(head, left);
			if (found) {
				found->count[i+1] = found->count[i+1] + node->count[i];
			} else {
				new = malloc(sizeof *new);
				memset(new, 0, sizeof *new);
				new->value = left;
				new->count[i+1] += node->count[i];
				new->next = head;
				head->prev = new;
				head = new;
			}
		}
	}
	result = 0;
	for (node = head; node; node = node->next) {
		result += node->count[i];
	}
	printf("%lu\n", result);
	return 0;
}
