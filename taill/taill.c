#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	long to_read = 10;
	if (argc < 2) {
		printf("%s [-n num] file\n", argv[0]);
		return 1;
	}

	int c;
	while ((c = getopt(argc, argv, ":n")) != -1) {
		switch(c) {
		case 'n':
			to_read = (long) atoi(argv[optind++]);
		}
	}

	int fd = open(argv[optind], O_RDONLY);
	if (fd == -1) {
		printf("Failed to open file: %s\n", argv[1]);
		return 1;
	}

	lseek(fd, to_read * -1, SEEK_END);

	char *buf = malloc(to_read);
	ssize_t numRead = read(fd, buf, to_read);

	if (numRead == -1) {
		printf("Failed to read from: %s\n", argv[1]);
		return 1;
	}

	printf("%s\n", buf);

	free(buf);
	close(fd);

	return 0;
}