#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	printf("%d", argc);
	if (argc != 3 && argc != 4) {
		printf("%s\n", "wrong numbers of args");
		return -1;
	}

	int isX = 0;
	if (argc == 4 && strcmp(argv[3], "x") == 0) {
		isX = 1;
	}

	int openFlags = O_CREAT | O_WRONLY;
	if (!isX) {
		openFlags |= O_APPEND;
	}

	int fd = open(argv[1], openFlags, 0644);

	long bytes = atol(argv[2]);
	char buf[1] = {'x'};
	for (long i = 0; i < bytes; i++) {
		if (isX) {
			int seek = lseek(fd, 0, SEEK_END);
			if (seek == -1) {
				printf("%s\n", "failed to seke end");
				return -1;
			}
		}

		ssize_t numWrote = write(fd, buf, 1);
		if (numWrote == -1) {
			printf("failed to write");
			return -1;
		}
	}

	close(fd);
	return 0;
}