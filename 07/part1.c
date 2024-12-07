#include <stdio.h>
#include <string.h>
#include <math.h>

static long long unsigned
parse_big_number(char *str)
{
	long long unsigned num = 0;
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
number_to_binary(unsigned num, unsigned length)
{
	static char buf[256];
	unsigned i = sizeof(buf) - 1;
	buf[i--] = 0;
	if (!num) {
		buf[i--] = '0';
		length--;
	}
	while (num) {
		buf[i--] = num % 2 ? '1' : '0';
		length--;
		num /= 2;
	}
	while (length) {
		buf[i--] = '0';
		length--;
	}
	return buf + i + 1;
}

int
main(void)
{
	char buf[4096], *binary;
	unsigned i,j;
	long long unsigned result;
	long long unsigned value;
	long long unsigned test;
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
		max = pow(2, count) -1;
		length = count;
		for (i=0; i<max; i++) {
			binary = number_to_binary(i, length);
			test = numbers[0];
			for (j=1; binary[j]; j++) {
				switch (binary[j]) {
				case '0':
					test += numbers[j];
					break;
				case '1':
					test *= numbers[j];
					break;
				}
			}
			if (value == test) {
				result += value;
				break;
			}
		}
	}
	printf("%llu\n", result);
	return 0;
}
