#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>

struct passwd *getuserbyname(const char *name) {
	struct passwd *pwd;
	while ((pwd = getpwent()) != NULL) {
		if (strcmp(name, pwd->pw_name) == 0) {
			return pwd;
		}
	}

	endpwent();

	return NULL;
}


// one arg of username
// loop through password file in /etc/pwd
// find entry with name
// return object!
int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("%s [username]\n", argv[0]);
		return 1;
	}

	struct passwd *pwd = getuserbyname(argv[1]);
	if (!pwd) {
		printf("Failed to find user: %s\n", argv[1]);
	} else {
		printf("%-8s %5ld\n", pwd->pw_name, (long) pwd->pw_uid);
	}

	return 0;
}