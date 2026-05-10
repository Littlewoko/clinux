#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUF_SIZE 100

int main(int argc, char *argv[]) {
	char buffer[BUF_SIZE];
	int outputFd, openFlags;
	mode_t filePerms;

	openFlags = O_CREAT | O_WRONLY;
	filePerms = S_IRUSR | S_IWUSR | S_IWGRP | S_IROTH | S_IWOTH;

	int opt;
	int appendOpt = 0;
	while ((opt = getopt(argc, argv, ":a")) != -1) {
		switch(opt) {
		case 'a':
			appendOpt = 1;
			break;
		}
	}

	if (appendOpt) {
		openFlags = openFlags | O_APPEND;
	} else {
		openFlags = openFlags | O_TRUNC;
	}

	outputFd = open(argv[optind], openFlags, filePerms);
	if (outputFd == -1) {
		printf("failed to open file");
		return -1;
	}

	while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
		char* toWrite = buffer;
		printf("%s", toWrite);
		int numWrite = write(outputFd, toWrite, strlen(toWrite));
		if (numWrite == -1) {
			printf("Writing failed\n");
			return -1;
		}
	}

	close(outputFd);


	return 0;
}