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
};

int main(void) {
	unsigned i;
	char buf[4096];
	unsigned result, count;
	struct stone *head, *node, *new;
	fgets(buf, sizeof buf, stdin);
	head = malloc(sizeof *head);
	node = head;
	node->next = 0;
	node->prev = 0;
	i = 0;
	while (1) {
		node->value = atoi(buf+i);
		while (buf[i] > ' ') i++;
		if (buf[i] == '\n') break;
		while (buf[i] == ' ') i++;
		new = malloc(sizeof *new);
		new->next = 0;
		new->prev = node;
		node->next = new;
		node = node->next;
	}
	for (i=0; i<25; i++)
	for (node=head; node; node=node->next) {
		// Rule 1
		if (node->value == 0) {
			node->value = 1;
			continue;
		}
		// Rule 2
		sprintf(buf, "%lu", node->value);
		count = strlen(buf);
		if ((count % 2) == 0) {
			new = malloc(sizeof *new);
			new->value = atoi(buf + (count/2));
			buf[count/2] = 0;
			node->value = atoi(buf);
			// Place NEW in place of HEAD as order does not matter.
			new->prev = 0;
			new->next = head;
			if (head->next) {
				head->next->prev = new;
			}
			head = new;
			continue;
		}
		// Rule 3
		node->value *= 2024;
	}
	result = 0;
	for (node = head; node; node = node->next) {
		result++;
	}
	printf("%u\n", result);
	return 0;
}
