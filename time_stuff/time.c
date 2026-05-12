#include <locale.h>
#include <time.h>
#include <sys/time.h>
#include "../lib/tlpi_hdr.h"

#define SECONDS_IN_TROPICAL_YEAR (365.24219 * 24 * 60 * 60)

int main(int argc, char *argv[]) {
	time_t t;
	struct tm *gmp, *locp;
	struct tm gm, loc;
	struct timeval tv;

	t = time(NULL);
	printf("Seconds since the epoch (1st jan 1970): %ld\n", (long) t);

	if (gettimeofday(&tv, NULL) == -1) {
		printf("gettimeofday");
		return 1;
	}

	printf("gettimeofday() returned %ld secs, %ld microsecs: ", (long) tv.tv_sec, (long) tv.tv_usec);

	gmp = gmtime(&t);
	if (gmp == NULL) {
		printf("gmtime");
		return 1;
	}

	gm = *gmp;

	printf("Broken down by gtmtime():\n");
	printf("year=%d mon=%d mday=%d hour=%d min=%d sec=%d \n", 
		gm.tm_year, gm.tm_mon, gm.tm_mday, gm.tm_hour, gm.tm_min, gm.tm_sec);

	locp = localtime(&t);
	if (locp == NULL) {
		printf("localtime");
		return 1;
	}
	loc = *locp;

	printf("Broken down by localtime():\n");
	printf("year=%d mon=%d mday=%d hour=%d min=%d sec=%d \n", 
		loc.tm_year, loc.tm_mon, loc.tm_mday, loc.tm_hour, loc.tm_min, loc.tm_sec);

	printf("asctime() formats the gmtime() value as: %s\n", asctime(&gm));
	printf("ctime() formats the time() value as: %s\n", ctime(&t));

	printf("mktime() of gmtime() value: %ld secs\n", (long) mktime(&gm));
	printf("mktime() of localtime() value: %ld secs\n", mktime(&loc));

	exit(EXIT_SUCCESS);
}