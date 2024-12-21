/*
  All "map" arrays follow the same general rules that allow for
  optimal solution.

  1. Avoid changing direction.  Because on next iteration robot will
     have to go back and forward between directional key and A key
     more time.

  2. Move to the left first when possible.  Left directional key is
     farthest from A key.  Moving there first makes followed moves
     smaller.  This is not always possible to do because of empty
     keys that we can't move to.  And it's better to stick to rule
     1 and avoid changing direction.

  3. Move ^> instead of >^ when possible.  The first combination
     will produce a need to press < key on next iteration and as
     explained in rule 2 - going left is least optimal.  This is
     also not always possible because of empty key that we have
     to avoid.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long unsigned directional(char *c, int repeat) {
	static const int indexof[] = {
		         ['^']=0, ['A']=4,
		['<']=3, ['v']=2, ['>']=1,
	};
	static char *map[5][5] = {	// [from][to]
	/*^*/	{"A","v>A","vA","v<A",">A"},
	/*>*/	{"<^A","A","<A","<<A","^A"},
	/*v*/	{"^A",">A","A","<A","^>A"},
	/*<*/	{">^A",">>A",">A","A",">>^A"},
	/*A*/	{"<A","vA","<vA","v<<A","A"},
	};
	static long unsigned cache[32][5][5] = {0};
	int from, to;
	long unsigned n=0;
	if (repeat == 0) {
		return strlen(c);
	}
	from = indexof['A'];
	for (; *c; c++) {
		to = indexof[(int)*c];
		if (!cache[repeat][from][to]) {
			cache[repeat][from][to] = directional(map[from][to], repeat-1);
		}
		n += cache[repeat][from][to];
		from = to;
	}
	return n;
}

static long unsigned numeric(char *c) {
	static const int indexof[] = {
		['7']=7, ['8']=8, ['9']=9,
		['4']=4, ['5']=5, ['6']=6,
		['1']=1, ['2']=2, ['3']=3,
		         ['0']=0, ['A']=10,
	};
	static char *map[11][11] = {	// [from][to]
	/*0*/	{"A","^<A","^A","^>A","^^<A","^^A","^^>A","^^^<A","^^^A","^^^>A",">A"},
	/*1*/	{"v>A","A",">A",">>A","^A","^>A","^>>A","^^A","^^>A","^^>>A",">>vA"},
	/*2*/	{"vA","<A","A",">A","<^A","^A","^>A","<^^A","^^A","^^>A",">vA"},
	/*3*/	{"<vA","<<A","<A","A","<<^A","<^A","^A","<<^^A","<^^A","^^A","vA"},
	/*4*/	{">vvA","vA","v>A","v>>A","A",">A",">>A","^A","^>A","^>>A",">>vvA"},
	/*5*/	{"vvA","<vA","vA","v>A","<A","A",">A","<^A","^A","^>A",">vvA"},
	/*6*/	{"<vvA","<<vA","<vA","vA","<<A","<A","A","<<^A","<^A","^A","vvA"},
	/*7*/	{">vvvA","vvA","vv>A","vv>>A","vA","v>A","v>>A","A",">A",">>A",">>vvvA"},
	/*8*/	{"vvvA","<vvA","vvA","vv>A","<vA","vA","v>A","<A","A",">A","vvv>A"},
	/*9*/	{"<vvvA","<<vvA","<vvA","vvA","<<vA","<vA","vA","<<A","<A","A","vvvA"},
	/*A*/	{"<A","^<<A","<^A","^A","^^<<A","<^^A","^^A","^^^<<A","<^^^A","^^^A","A"},
	};
	int from, to;
	long unsigned n=0;
	from = indexof['A'];
	for (; *c; c++) {
		to = indexof[(int)*c];
		n += directional(map[from][to], 25);
		from = to;
	}
	return n;
}

int main(void) {
	char buf[4096];
	long unsigned result=0;
	while (scanf("%s\n", buf) > 0) {
		result += atoi(buf) * numeric(buf);
	}
	printf("%lu\n", result);
	return !(result == 154115708116294 || result == 252473394928452);
}
