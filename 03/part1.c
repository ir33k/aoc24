#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <regex.h>

char *
get_stdin(void)
{
	static char *buf;
	const size_t siz = 20*1024;	// 20 KB should be enough for everyon, right? ^-^
	buf = malloc(siz);
	if (!buf) {
		err(1, 0);
	}
	if (read(STDIN_FILENO, buf, siz) >= (ssize_t)siz) {
		errx(1, "read");
	}
	return buf;
}

char *
get_regex_error(int code)
{
	switch (code) {
	case REG_NOMATCH:  return "The regexec() function failed to match";
	case REG_BADPAT:   return "invalid regular expression";
	case REG_ECOLLATE: return "invalid collating element";
	case REG_ECTYPE:   return "invalid character class";
	case REG_EESCAPE:  return "‘\\’ applied to unescapable character";
	case REG_ESUBREG:  return "invalid backreference number";
	case REG_EBRACK:   return "brackets ‘[ ]’ not balanced";
	case REG_EPAREN:   return "parentheses ‘( )’ not balanced";
	case REG_EBRACE:   return "braces ‘{ }’ not balanced";
	case REG_BADBR:    return "invalid repetition count(s) in ‘{ }’";
	case REG_ERANGE:   return "invalid character range in ‘[ ]’";
	case REG_ESPACE:   return "ran out of memory";
	case REG_BADRPT:   return "‘?’, ‘*’, or ‘+’ operand invalid";
	case REG_EMPTY:    return "empty (sub)expression";
	case REG_ASSERT:   return "cannot happen - you found a bug";
	case REG_INVARG:   return "invalid argument, e.g. negative-length string";
	case REG_ILLSEQ:   return "illegal byte sequence (bad multibyte character)";
	}
	return "Unknown error code";
}

int
main(void) {
	char *buf;
	int code;
	unsigned sum;
	regex_t preg;
	regmatch_t pmatch[3];
	buf = get_stdin();
	if ((code = regcomp(&preg, "mul\\(([0-9]+),([0-9]+)\\)", REG_EXTENDED))) {
		errx(1, "regcomp %s", get_regex_error(code));
	}
	sum = 0;
	while (regexec(&preg, buf, 3, pmatch, 0) == 0) {
		/* printf("%lld %lld %.*s %d %d\n", */
		/*        pmatch[0].rm_so, */
		/*        pmatch[0].rm_eo, */
		/*        (int)(pmatch[0].rm_eo - pmatch[0].rm_so), */
		/*        buf + pmatch[0].rm_so, */
		/*        atoi(buf + pmatch[1].rm_so), */
		/*        atoi(buf + pmatch[2].rm_so)); */
		sum += atoi(buf + pmatch[1].rm_so) *
		       atoi(buf + pmatch[2].rm_so);
		buf += pmatch[0].rm_eo;
	}
	printf("%u\n", sum);
	return 0;
}
