#include "ehstr.h"		/* revstr */

#include <stdio.h>		/* fprintf */
#include <string.h>		/* strncpy */
#include "echeck.h"		/* check_str */

int main(void)
{
	int failures;
	char expected[10], reverse[10];

	failures = 0;
	strncpy(expected, "edcba", 10);
	strncpy(reverse, "abcde", 10);

	revstr(reverse, 10);

	failures += check_str(reverse, expected);

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return (failures > 127 || failures < -128) ? 127 : failures;
}
