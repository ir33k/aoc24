#include <assert.h>
#include <stdio.h>
#include <math.h>

static long unsigned
parse_long(char *str)
{
	long unsigned num = 0;
	for (; *str >= '0' && *str <= '9'; str++) {
		num = num * 10 + (*str - '0');
	}
	return num;
}

static char *
stringify(unsigned num, unsigned base, unsigned lpad)
{
	static char buf[16];
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

int
main(void)
{
	char buf[4096], *str;
	unsigned i,j;
	long unsigned result;
	long unsigned value;
	long unsigned test;
	unsigned numbers[256], count, max;
	result = 0;
	while (fgets(buf, sizeof buf, stdin)) {
		value = parse_long(buf);
		count = 0;
		i = 0;
		while (1) {
			while (buf[i] > ' ') i++;
			if (buf[i] == '\n') break;
			while (buf[i] == ' ') i++;
			numbers[count++] = parse_long(buf+i);
		}
		max = pow(2, count) -1;
		for (i=0; i<max; i++) {
			str = stringify(i, 2, count);
			test = numbers[0];
			for (j=1; str[j]; j++) {
				switch (str[j]) {
				case '0': test += numbers[j]; break;
				case '1': test *= numbers[j]; break;
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
