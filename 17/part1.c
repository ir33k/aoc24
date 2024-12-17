#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	char buf[4096];
	int i, opcode, operand, combo;
	int program[32];	// List of instructions
	int icount=0;		// Instructions count
	int reg_a=0, reg_b=0, reg_c=0;
	scanf("Register A: %d\n", &reg_a);
	scanf("Register B: %d\n", &reg_b);
	scanf("Register C: %d\n", &reg_c);
	fgets(buf, sizeof buf, stdin);	// Skip line
	fgets(buf, sizeof buf, stdin);
	i=0;
	while (buf[i] != ' ') i++;
	for (i++; buf[i]; i++) {
		program[icount++] = atoi(buf+i);
		while (buf[i] > ',') i++;
	}
	for (i=0; i<icount; i+=2) {
		opcode = program[i];
		operand = program[i+1];
		combo = operand;
		switch (operand) {
		case 4: combo = reg_a; break;
		case 5: combo = reg_b; break;
		case 6: combo = reg_c; break;
		}
		switch (opcode) {
		case 0: reg_a = reg_a / pow(2, combo); break;
		case 1: reg_b = reg_b ^ operand;       break;
		case 2: reg_b = combo % 8;             break;
		case 3: if (reg_a != 0) i = operand-2; break;
		case 4: reg_b = reg_b ^ reg_c;         break;
		case 5: printf("%d,", combo % 8);      break;
		case 6: reg_b = reg_a / pow(2, combo); break;
		case 7: reg_c = reg_a / pow(2, combo); break;
		}
	}
	printf("\b\n");
	return 0;
}
