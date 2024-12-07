#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static long unsigned
parse_big_number(char *str)
{
	long unsigned num = 0;
	size_t i = 0;
	for (i = 0; str[i] >= '0' && str[i] <= '9'; i++) {
		num += str[i] - '0';
		if (str[i+1] >= '0' && str[i+1] <= '9') {
			num *= 10;
		}
	}
	return num;
}

static char *
number_to_ternary(unsigned num, unsigned length)
{
	static char buf[256];
	unsigned i = sizeof(buf) - 1;
	buf[i--] = 0;
	if (!num) {
		buf[i--] = '0';
		length--;
	}
	while (num) {
		buf[i--] = num % 3 + '0';
		length--;
		num /= 3;
	}
	while (length) {
		buf[i--] = '0';
		length--;
	}
	return buf + i + 1;
}

static long unsigned
concatenate(long unsigned a, long unsigned b)
{
	unsigned pow = 10;
	while (b >= pow) {
		pow *= 10;
	}
	return a * pow + b;        
}

int
main(void)
{
	char buf[4096], *ternary;
	unsigned i,j;
	long unsigned result;
	long unsigned value;
	long unsigned test;
	unsigned numbers[256], count, max, length;
	result = 0;
	while (fgets(buf, sizeof buf, stdin)) {
		value = parse_big_number(buf);
		count = 0;
		i = 0;
		while (1) {
			while (buf[i] > ' ') i++;
			if (buf[i] == '\n') break;
			while (buf[i] == ' ') i++;
			numbers[count++] = parse_big_number(buf+i);
		}
		max = pow(3, count) -1;
		length = count;
		for (i=0; i<max; i++) {
			ternary = number_to_ternary(i, length);
			test = numbers[0];
			for (j=1; ternary[j]; j++) {
				switch (ternary[j]) {
				case '0':
					test += numbers[j];
					break;
				case '1':
					test *= numbers[j];
					break;
				case '2':	// the || operator
					test = concatenate(test, numbers[j]);
					break;
				}
			}
			if (value == test) {
				result += value;
				break;
			}
		}
	}
	printf("%lu\n", result);
	return 0;
}
