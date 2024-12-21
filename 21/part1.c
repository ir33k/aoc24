/*
  All static "map" arrays follow the same rules allowing for optimal
  solution.  List of rules from the most to the least important:

  1. Avoid changing direction.  Because on next iteration robot will
     have to go back and forward between directional key and A key
     each time the direction key change.

  2. Move to the left first when possible.  Left directional key is
     farthest from A key making it the most expensive.  Moving to the
     left first makes other followed moves smaller.  It's not possible
     to start moving to the left in all combinations because of the
     empty key.  In that situation just stick to the first rule.

  3. Use ^>A instead of >^A when possible.  First combination produce
     shorter sequence after 2 more iterations.

     ^>A (3)-> <Av>A^A (7)-> v<<A>>^Av<A>A^A<A>A   (19)-> ...
     >^A (3)-> vA<^A>A (7)-> v<A>^Av<<A>^A>Av<A>^A (21)-> ...
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int dir_indexof[] = {	// Directional keypad key indexes
	/* -- */ ['^']=0, [ 0 ]=4,
	['<']=3, ['v']=2, ['>']=1,
};
static char *dir_map[16][16] = {	// [from][to] key combinations
/*^*/	{"","v>","v","v<",">"},
/*>*/	{"<^","","<","<<","^"},
/*v*/	{"^",">","","<","^>"},
/*<*/	{">^",">>",">","",">>^"},
/*A*/	{"<","v","<v","v<<",""},
};
static const int num_indexof[] = {	// Numeric keypad key indexes
	['7']=7, ['8']=8, ['9']=9,
	['4']=4, ['5']=5, ['6']=6,
	['1']=1, ['2']=2, ['3']=3,
	/* -- */ ['0']=0, [ 0 ]=10,
};
static char *num_map[16][16] = {	// [from][to] key combinations
/*0*/	{"","^<","^","^>","^^<","^^","^^>","^^^<","^^^","^^^>",">"},
/*1*/	{"v>","",">",">>","^","^>","^>>","^^","^^>","^^>>",">>v"},
/*2*/	{"v","<","",">","<^","^","^>","<^^","^^","^^>",">v"},
/*3*/	{"<v","<<","<","","<<^","<^","^","<<^^","<^^","^^","v"},
/*4*/	{">vv","v","v>","v>>","",">",">>","^","^>","^>>",">>vv"},
/*5*/	{"vv","<v","v","v>","<","",">","<^","^","^>",">vv"},
/*6*/	{"<vv","<<v","<v","v","<<","<","","<<^","<^","^","vv"},
/*7*/	{">vvv","vv","vv>","vv>>","v","v>","v>>","",">",">>",">>vvv"},
/*8*/	{"vvv","<vv","vv","vv>","<v","v","v>","<","",">","vvv>"},
/*9*/	{"<vvv","<<vv","<vv","vv","<<v","<v","v","<<","<","","vvv"},
/*A*/	{"<","^<<","<^","^","^^<<","<^^","^^","^^^<<","<^^^","^^^",""},
};

static long unsigned
click(const int indexof[], char *map[16][16], char *str, int robot)
{
	static long unsigned cache[32][16][16] = {0};	// [robot][from][to]
	int from, to;
	long unsigned n=0;
	if (robot == 0) {
		return strlen(str) +1;	// +1 for A key
	}
	from = indexof[0];	// Start with A key
	while (1) {
		to = indexof[(int)*str];
		if (!cache[robot][from][to]) {
			cache[robot][from][to] = click(dir_indexof, dir_map, map[from][to], robot-1);
		}
		n += cache[robot][from][to];
		if (!*str) {
			break;
		}
		from = to;
		str++;
	}
	return n;
}

int main(void) {
	char buf[4096];
	long unsigned result=0;
	while (scanf("%[0-9]A\n", buf) > 0) {
		result += atoi(buf) * click(num_indexof, num_map, buf, 3);
	}
	printf("%lu\n", result);
	return !(result == 126384 || result == 205160);
}
