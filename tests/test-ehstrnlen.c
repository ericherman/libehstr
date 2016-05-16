#include "../src/ehstr.h"	/* ehstrnlen */

#include <stdio.h>		/* fprintf */
#include <echeck.h>		/* check_unsigned_int */
#include <string.h>		/* perhaps strnlen */

int main()
{
	int failures = 0;
	char *foo = "foo";

	failures += check_unsigned_int(3, ehstrnlen(foo, 100));
	failures += check_unsigned_int(2, ehstrnlen(foo, 2));

	failures += check_unsigned_int(strnlen(foo, 100), ehstrnlen(foo, 100));
	failures += check_unsigned_int(strnlen(foo, 2), ehstrnlen(foo, 2));

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return failures;
}
