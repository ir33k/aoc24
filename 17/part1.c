#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	char buf[4096];
	int program[32];	// List of instructions
	int i, n=0;		// Index and number of instructions
	int a=0, b=0, c=0;	// Registers
	int op, combo;		// Operand and combo value
	scanf("Register A: %d\n", &a);
	scanf("Register B: %d\n", &b);
	scanf("Register C: %d\n", &c);
	fgets(buf, sizeof buf, stdin);	// Skip line
	fgets(buf, sizeof buf, stdin);
	i=0;
	while (buf[i] != ' ') i++;
	for (i++; buf[i]; i+=2) {
		program[n++] = atoi(buf+i);
	}
	for (i=0; i<n; i+=2) {
		op = program[i+1];
		combo = op;
		switch (op) {
		case 4: combo = a; break;
		case 5: combo = b; break;
		case 6: combo = c; break;
		}
		switch (program[i]) {
		case 0: a /= pow(2, combo); break;
		case 1: b ^= op; break;
		case 2: b  = combo % 8; break;
		case 3: if (a) i = op-2; break;
		case 4: b ^= c; break;
		case 5: printf("%d,", combo % 8); break;
		case 6: b = a / pow(2, combo); break;
		case 7: c = a / pow(2, combo); break;
		}
	}
	printf("\b\n");
	return 0;
}
