#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct gate {
	char left[4], logic[4], right[4], output[4];
};

static int x[45]={0};
static int y[45]={0};
static int vi=0;	// Input x,y values count
static int z[45]={0};
static int zi=0;	// Output z values count

static struct gate gates[256];
static int gi=0;	// Gates count

static long unsigned to_decimal(int array[], int length) {
	int i;
	long unsigned result=0;
	for (i=0; i<length; i++) {
		result += pow(2, i) * array[i];
	}
	return result;
}

static char *stringify(unsigned num, unsigned base, unsigned lpad) {
	static char buf[64];
	unsigned i = sizeof buf;
	assert(sizeof buf > lpad);
	buf[--i] = 0;
	while (num && lpad--) {
		buf[--i] = num % base + '0';
		num /= base;
	}
	while (lpad--) {	// Left pad
		buf[--i] = '0';
	}
	return buf + i;
}

static int gate_indexof(char *output) {
	int i;
	for (i=0; i<gi; i++) {
		if (!strcmp(gates[i].output, output)) {
			return i;
		}
	}
	assert(0 && "Unreachable");
	return -1;
}

static int compute(char *output) {
	struct gate gate;
	int left, right;
	switch (output[0]) {
	case 'x': return x[atoi(output+1)];
	case 'y': return y[atoi(output+1)];
	}
	gate  = gates[gate_indexof(output)];
	left  = compute(gate.left);
	right = compute(gate.right);
	/* printf("%c", gate.logic[0]); */
	/* printf("%s %s %s -> %s\n", */
	/*        gate.left, */
	/*        gate.logic, */
	/*        gate.right, */
	/*        gate.output); */
	switch (gate.logic[0]) {
	case 'A': return left && right;
	case 'O': return left || right;
	case 'X': return left != right;
	}
	assert(0 && "Unreachable");
	return -1;
}

static int compar(const void *a, const void *b) {
	struct gate *g1 = (struct gate *)a;
	struct gate *g2 = (struct gate *)b;
	return strcmp(g1->output, g2->output);
}

int main(void) {
	long unsigned result=0, sum=0;
	char buf[4096], wire;
	int i,j, value;
	struct gate gate;
	// Get initial x and y input values
	while (fgets(buf, sizeof buf, stdin)) {
		if (buf[0] == '\n') {
			break;
		}
		sscanf(buf, "%c%d: %d\n", &wire, &i, &value);
		switch (wire) {
		case 'x': x[i] = value; break;
		case 'y': y[i] = value; break;
		}
		if (i > vi) vi = i;
	}
	vi++;
	sum = to_decimal(x, vi) + to_decimal(y, vi);
	// Get logic
	while (scanf("%s %s %s -> %s\n",
		     gates[gi].left,
		     gates[gi].logic,
		     gates[gi].right,
		     gates[gi].output) > 0) {
		gate = gates[gi];
		if ((gate.output[0] == 'z' &&
		     atoi(gate.output+1) != 45 &&
		     gate.logic[0] != 'X') ||
		    (gate.output[0] != 'z' &&
		     gate.left[0] != 'x' &&
		     gate.left[0] != 'y' &&
		     gate.right[0] != 'x' &&
		     gate.right[0] != 'y' &&
		     gate.logic[0] == 'X')) {
			printf("%s %s %s -> %s\n",
			       gate.left,
			       gate.logic,
			       gate.right,
			       gate.output);
		}

		gi++;
	}
	// Sort logic
	qsort(gates, gi, sizeof gates[0], compar);
	/* for (i=0; i<gi; i++) { */
	/* 	printf("%s\n", gates[i].output); */
	/* } */
	//
	for (i=0; i<gi; i++) {
		if (gates[i].output[0] != 'z') {
			continue;
		}
		/* printf("%s ", gates[i].output); */
		j = atoi(gates[i].output+1);
		z[j] = compute(gates[i].output);
		if (j > zi) {
			zi = j;
		}
		/* printf("\n"); */
	}
	zi++;
	//
	result = to_decimal(z, zi);
	printf("%lu %s sum\n", sum, stringify(sum, 2, zi));
	printf("%lu %s result\n", result, stringify(result, 2, zi));
	return !(result == sum);
}
