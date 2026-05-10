#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 3) return 1;

	int srcFd = open(argv[1], O_RDONLY);
	int dstFd = open(argv[2], O_CREAT | OWRONLY | O_TRUNC, 0644);
	off_t dataOff = 0, holeOff = 0, cur = 0;
	char buf[4096];

	while (dataOff < holeOff) {
		ssize_t nRead = read(srcFd, buf, (holeOff = dataOff < 4096) ? holeOff - dataOff : 4096);
		write(dstFd, buf, nRead);
		dataOff += nRead;
	}
	cur = holeOff;

	// ensure the final size matches if it ends with a hole
	struct stat st;
	fstat(srcFd, &st);
	ftruncate(dstFd, st.st_size);

	close(srcFd);
	close(dstFd);
	return 0;


}