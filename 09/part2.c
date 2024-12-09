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
	unsigned blocks, free_space;
	size_t i,j,k, file_id, block_position, j_beg, used_count;
	int used[20000] = {0};
	buf = get_stdin();
	i = 0;			// Index going from start
	j_beg = strlen(buf) -2;	// Index going from end
	if (!IS_FILE(j_beg)) {
		j_beg--;
	}
	used_count = j_beg / 2 + 1;
	free_space = 0;
	block_position = 0;
	result = 0;
	while (used_count > 0) {
		// From start
		blocks = buf[i] - '0';
		file_id = FILE_ID(i);
		i++;
		if (used[file_id]) {
			free_space = blocks;
			block_position += free_space;
		} else {
			used[file_id] = 1;
			used_count--;
			for (k=0; k<blocks; k++) {
				printf("%lu", file_id);
				result += file_id * block_position;
				block_position++;
			}
		}
		free_space = buf[i] - '0';
		i++;
		// From end
		while (free_space) {
			j = j_beg;
			do {
				blocks = buf[j] - '0';
				file_id = FILE_ID(j);
				j -= 2;
			} while (j>0 && (used[file_id] || blocks > free_space));
			if (j<=0) {
				block_position += free_space;
				break;
			}
			used[file_id] = 1;
			used_count--;
			free_space -= blocks;
			while (blocks--) {
				printf("%lu", file_id);
				result += file_id * block_position;
				block_position++;
			}
		}
	}
	printf("\n");
	printf("%lu\n", result);
	return 0;
}
