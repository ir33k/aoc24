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
	/* printf("%s %3.3s %s -> %s\n", gate.left, gate.logic, gate.right, output); */
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
	long unsigned result, sum;
	char buf[4096], wire, swap[4];
	int i,k,g, value;
	int swap_i, swap_j, ok;
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
		#define FROM "z21"
		#define TO   "gmq"
		/**/ if (!strcmp(gates[gi].output, FROM)) strcpy(gates[gi].output, TO  );
		else if (!strcmp(gates[gi].output, TO  )) strcpy(gates[gi].output, FROM);
		#undef FROM
		#undef TO
		#define FROM "z05"
		#define TO   "frn"
		/**/ if (!strcmp(gates[gi].output, FROM)) strcpy(gates[gi].output, TO  );
		else if (!strcmp(gates[gi].output, TO  )) strcpy(gates[gi].output, FROM);
		#undef FROM
		#undef TO
		#define FROM "z39"
		#define TO   "wtt"
		/**/ if (!strcmp(gates[gi].output, FROM)) strcpy(gates[gi].output, TO  );
		else if (!strcmp(gates[gi].output, TO  )) strcpy(gates[gi].output, FROM);
		#undef FROM
		#undef TO
		#define FROM "wnf"
		#define TO   "vtj"
		/**/ if (!strcmp(gates[gi].output, FROM)) strcpy(gates[gi].output, TO  );
		else if (!strcmp(gates[gi].output, TO  )) strcpy(gates[gi].output, FROM);
		gi++;
	}
	// Sort logic
	qsort(gates, gi, sizeof gates[0], compar);
	for (i=0; i<45; i++) {
		x[i] = 1;
		y[i] = 1;
		sum = to_decimal(x, 45) + to_decimal(y, 45);
		/* printf("%s %d\n", stringify(to_decimal(x, 45), 2, 46), i); */
		/* printf("%s %d\n", stringify(to_decimal(y, 45), 2, 46), i); */
		for (g=0; g<gi; g++) {
			if (gates[g].output[0] != 'z') {
				continue;
			}
			k = atoi(gates[g].output+1);
			z[k] = compute(gates[g].output);
			if (k > zi) {
				zi = k;
			}
		}
		result = to_decimal(z, zi+1);
		/* printf("%s sum\n", stringify(sum, 2, zi+1)); */
		/* printf("%s result\n", stringify(result, 2, zi+1)); */
		x[i] = 0;
		y[i] = 0;
		if (result != sum) {
			printf("mismatch at: %d\n", i);
			continue;
		}
	}
	//
	/* for (g=0; g<gi; g++) { */
	/* 	if (gates[g].output[0] != 'z') { */
	/* 		continue; */
	/* 	} */
	/* 	k = atoi(gates[g].output+1); */
	/* 	/\* printf("z%d ----------------\n", k); *\/ */
	/* 	z[k] = compute(gates[g].output); */
	/* 	if (k > zi) { */
	/* 		zi = k; */
	/* 	} */
	/* } */
	/* for (swap_i=9; swap_i<gi; swap_i++) */
	/* for (swap_j=swap_i+1; swap_j<gi; swap_j++) { */
	/* 	printf("%d %d %s %s\n", */
	/* 	       swap_i, */
	/* 	       swap_j, */
	/* 	       gates[swap_i].output, */
	/* 	       gates[swap_j].output); */
	/* 	strcpy(swap, gates[swap_i].output); */
	/* 	strcpy(gates[swap_i].output, gates[swap_j].output); */
	/* 	strcpy(gates[swap_j].output, swap); */
	/* 	for (i=0; i<45; i++) { */
	/* 		y[i] = 1; */
	/* 		sum = to_decimal(x, 45) + to_decimal(y, 45); */
	/* 		/\* printf("%s %d\n", stringify(to_decimal(y, 45), 2, 46), i); *\/ */
	/* 		for (g=0; g<gi; g++) { */
	/* 			if (gates[g].output[0] != 'z') { */
	/* 				continue; */
	/* 			} */
	/* 			k = atoi(gates[g].output+1); */
	/* 			z[k] = compute(gates[g].output); */
	/* 			if (k > zi) { */
	/* 				zi = k; */
	/* 			} */
	/* 		} */
	/* 		result = to_decimal(z, zi+1); */
	/* 		/\* printf("%s sum\n", stringify(sum, 2, zi+1)); *\/ */
	/* 		/\* printf("%s result\n", stringify(result, 2, zi+1)); *\/ */
	/* 		y[i] = 0; */
	/* 		if (result != sum) { */
	/* 			printf("mismatch at: %d\n", i); */
	/* 			continue; */
	/* 		} */
	/* 	} */
	/* 	strcpy(swap, gates[swap_i].output); */
	/* 	strcpy(gates[swap_i].output, gates[swap_j].output); */
	/* 	strcpy(gates[swap_j].output, swap); */
	/* } */
	return 0;
}
