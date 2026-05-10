#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


extern char **environ;

int setEnvironment(char *name, char *value, int toOverwrite) {
    // 1. Check if the variable exists (if overwrite is disabled)
    if (!toOverwrite && getenv(name) != NULL) {
        return 0; 
    }

    // 2. Calculate length: name + '=' + value + '\0'
    int totalLen = strlen(name) + 1 + strlen(value) + 1;

    // 3. Allocate persistent memory on the Heap
    // putenv requires this memory to stay alive for the life of the program
    char *envString = malloc(totalLen);
    if (envString == NULL) {
        return -1;
    }

    // 4. Build the string: "NAME=VALUE"
    // sprintf is much easier than manual loops!
    sprintf(envString, "%s=%s", name, value);

    // 5. Pass to putenv
    int outcome = putenv(envString);
    
    if (outcome != 0) {
        perror("putenv failed"); // perror gives more detail on errors
        free(envString);         // Only free if it fails
        return -1;
    }

    return 0;
}

int unsetEnvironment(char *name) {
	if (getenv(name) == NULL) {
		return 0;
	}

	putenv(name);
}


int main(int argc, char *argv[]) {
	char **ep;

	setEnvironment("HELLO", "WORLD", 0);
	setEnvironment("HELLO", "PIGS", 0);

	unsetEnvironment("HELLO");

	for (ep = environ; *ep != NULL; ep++) {
		puts(*ep);
	}

	return 0;
}
