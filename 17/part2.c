#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MOD(a,b) (((a) % (b) + (b)) % (b))

int main(void) {
	char buf[4096];
	int program[32];	// List of instructions
	int output[32];
	int i,j,k,k2,l, n=0;		// Index and number of instructions
	long long unsigned a=0, b=0, c=0;	// Registers
	int b_init, c_init;
	int op, combo;		// Operand and combo value
	long long unsigned m;
	scanf("Register A: %d\n", &b_init);
	scanf("Register B: %d\n", &b_init);
	scanf("Register C: %d\n", &c_init);
	fgets(buf, sizeof buf, stdin);	// Skip line
	fgets(buf, sizeof buf, stdin);
	i=0;
	while (buf[i] != ' ') i++;
	for (i++; buf[i]; i+=2) {
		program[n++] = atoi(buf+i);
	}
	m = 40107153110;
	l = 0;
	while (1) {
		a = m + l;
		b = b_init;
		c = c_init;
		j=0;
		for (i=0; i<n;) {
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
			case 2: b  = MOD(combo, 8); break;
			case 3: if (a) i = op-2; break;
			case 4: b ^= c; break;
			case 5: output[j++] = MOD(combo, 8); break;
			case 6: b = a / pow(2, combo); break;
			case 7: c = a / pow(2, combo); break;
			}
			i+=2;
		}
		if (j == 0) {
			goto next;
		}
		if (j > n) {
			printf("1\n");
			goto next;
		}
		
		for (k=n-1, k2=j-1; k2>=0; k2--,k--) {
			/* printf("%d %d\n", program[k], output[k2]); */
			if (program[k] != output[k2]) {
				goto next;
			}
		}

		printf("found %llu\n", m+l);
		m = (m+l) << 3;
		l = 0;
		goto found;

		if (k != 0) {
			goto next;
		}
		printf("%llu	", m);
		for (k=0; k<j; k++) {
			printf("%d,", output[k]);
		}
		printf("\n");
		break;
	next:
		/* printf("FAIL %llu\n", m+l); */
		if (l<7) {
			l++;
			continue;
		}
		l = 0;
		m = (m>>3) +1;
		continue;
	found:
		printf("FOUND	");
		for (k=0; k<j; k++) {
			printf("%d,", output[k]);
		}
		printf("\n");
		continue;
	}
	printf("%llu\n", m);
	return m != 164278899142333;
}
/*
      4	000 000 000 000 000 000 000 100	              0
     37	000 000 000 000 000 000 100 101	            3,0
    298	000 000 000 000 000 100 101 010	          3,3,0
   2390	000 000 000 000 100 101 010 110	        0,3,3,0
  19124	000 000 000 100 101 010 110 100	      5,0,3,3,0
 152996	000 000 100 101 010 110 100 100	    5,5,0,3,3,0
1223973	000 100 101 010 110 100 100 101	  3,5,5,0,3,3,0
9791785	100 101 010 110 100 100 101 001	4,3,5,5,0,3,3,0

298	3,3,0,
301	3,3,0,

2390	0,3,3,0,
2408	0,3,3,0,
2414	0,3,3,0,

152996	5,5,0,3,3,0,
152999	5,5,0,3,3,0,
154155	5,5,0,3,3,0,


      4                             100               0
     37	                        100 101	            0,3
    298	                    100 101 010	          0,3,3
   2390	                100 101 010 110	        0,3,3,0
  19124	            100 101 010 110 100	      0,3,3,0,5
 152996	        100 101 010 110 100 100	    0,3,3,0,5,5
1223973	    100 101 010 110 100 100 101	  0,3,3,0,5,5,3
9791785	100 101 010 110 100 100 101 001	0,3,3,0,5,5,3,4

40107153110	100 101 010 110 100 100 101 001 011 011 010110
320857224887
2566857799098
20534862392784


9791785 
78334280 
626674240 
5013393920 

100
100 101
100 101 010
100 101 010 110
100 101 010 110 100
100 101 010 110 100 100
100 101 010 110 100 100 101
100 101 010 110 100 100 101 001


 */
