#include <setjmp.h>
#include <stdio.h>

static jmp_buf env;

int setJump(void) {
	setjmp(env);
	printf("%s\n", "Hello, world");
}


int main(int argc, char *argv[]) {
	setJump();

	longjmp(env, 1);

	return 0;
}