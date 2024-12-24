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
	switch (gate.logic[0]) {
	case 'A': return left && right;
	case 'O': return left || right;
	case 'X': return left != right;
	}
	assert(0 && "Unreachable");
	return -1;
}

int main(void) {
	long unsigned result=0;
	char buf[4096], wire;
	int i,j, value;
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
	// Get logic
	while (scanf("%s %s %s -> %s\n",
		     gates[gi].left,
		     gates[gi].logic,
		     gates[gi].right,
		     gates[gi].output) > 0) {
		gi++;
	}
	//
	for (i=0; i<gi; i++) {
		if (gates[i].output[0] != 'z') {
			continue;
		}
		j = atoi(gates[i].output+1);
		z[j] = compute(gates[i].output);
		if (j > zi) {
			zi = j;
		}
	}
	zi++;
	//
	result = 0;
	for (i=0; i<zi; i++) {
		result += pow(2, i) * z[i];
	}
	printf("%lu\n", result);
	return !(result == 2024 || result == 56939028423824);
}
