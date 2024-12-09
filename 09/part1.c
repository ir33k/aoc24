#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define IS_FILE(x) (!((x) % 2))
#define FILE_ID(x) ((unsigned)((x)/2))

static char *
get_stdin(void)
{
	static char *buf;
	const size_t siz = 32*1024;	// 32 KB should be enough for everyon, right? ^-^
	if (!(buf = malloc(siz))) {
		err(1, 0);
	}
	if (read(STDIN_FILENO, buf, siz) >= (ssize_t)siz) {
		errx(1, "read");
	}
	return buf;
}

int main(void) {
	char *buf;
	long unsigned result;
	unsigned blocks, end_blocks, free_space;
	size_t i,j,k, file_id, block_position;
	buf = get_stdin();
	i = 0;			// Index going from start
	j = strlen(buf) -2;	// Index going from end
	if (!IS_FILE(j)) {
		j--;
	}
	free_space = 0;
	block_position = 0;
	end_blocks = 0;
	result = 0;
	while (i < j) {
		// From start
		blocks = buf[i] - '0';
		file_id = FILE_ID(i);
		for (k=0; k<blocks; k++) {
			result += file_id * block_position;
			block_position++;
		}
		i++;
		free_space = buf[i] - '0';
		i++;
		// From end
		while (free_space) {
			if (!end_blocks) {
				end_blocks = buf[j] - '0';
			}
			file_id = FILE_ID(j);
			k = end_blocks < free_space ? end_blocks : free_space;
			free_space -= k;
			end_blocks -= k;
			if (!end_blocks) {
				j -= 2;
			}
			while (k--) {
				result += file_id * block_position;
				block_position++;
			}
		}
	}
	while (end_blocks--) {
		result += file_id * block_position;
		block_position++;
	}
	printf("\n");
	printf("%lu\n", result);
	return 0;
}
