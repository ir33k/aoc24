/*
How does it work?

I realized that each lock and key can be represented as single number.
It's easy to see in binary that all we have to do is to check if the
number representing lock don't have '1' that overlap with '1' from
number representing key.  We do that with bitwise operator AND.  If
resulted value is not a 0 then we have overlap.

	lock   bin      key    bin      AND
	-----  -----    -----  -----    -----
	#####  11111    .....  00000    00000
	##.##  11011    #....  10000    10000
	.#.##  01011    #....  10000    00000
	...##  00011    #...#  10001    00001
	...#.  00010    #.#.#  10101    00000
	...#.  00010    #.###  10111    00010
	.....  00000    #####  11111    00000

	lock  11111 11011 01011 00011 00010 00010 00000
	key   00000 10000 10000 10001 10101 10111 11111
	AND   00000 10000 00000 00001 00000 00010 00000

AoC task description made us believe that first and last line of the
lock/key are just an indication if given shape is lock or key.  But
with this approach we can include them.  This simplify input parsing.
Also we don't have to think of the "pins" as vertical lines.  With
this strategy it does not matter if we convert pins to binary as
horizontal or vertical lines.

Another revelation that this brings is that we don't have to separate
keys from locks.  I used single table for both.  This is because lock
will always produce non 0 value when you use AND operator on another
lock.  This is thanks to first line in input for each lock/key.  When
we use single array then we have to test all values with all other
values, so we are wasting time on checking locks with locks and keys
with keys.  This is still very fast because result is validated with
single bitwise AND.

There are other small improvements like 0 terminated array.  With
"normal" code for this AoC day solution I had to track size for locks
and keys arrays.  Now I just 0 initialize the list and I know for sure
that binary representation of locks and keys don't produce 0.  Another
thing is that I just read input character by character and I know that
each lock/key is 43 bytes long.  This includes \n characters but those
will become 0 so they have no effect on the algorithm.  But having
this 43 magic number I can divide character index to determinate on
which lock/key I'm in and calculate MOD of that index to know which
bite to set.

	"The C Side of the Code is a pathway to many
	abilities some consider to be unnatural."
*/
#include <stdio.h>

int main(void) {
	long i,j, list[512]={0}, sum=0;
	for (i=0; (j = getchar()) > 0; i++) {
		list[i/43] |= (long)(j=='#') << (i%43);
	}
	for (i=0; list[i]; i++)
	for (j=i; list[j]; j++) {
		sum += !(list[i] & list[j]);
	}
	printf("%ld\n", sum);
	return sum != 3327;
}
