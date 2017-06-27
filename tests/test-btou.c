#include "ehstr.h"		/* nothing */

#include <stdio.h>		/* fprintf */
#include <stdlib.h>		/* strtol strtoul */
#include "echeck.h"		/* check_long check_unsigned_long */

int main(void)
{
	unsigned long result;
	int failures;
	int base2;

	failures = 0;

	base2 = 2;
	result = strtol("0101", NULL, base2);
	failures += check_long(result, 5);

	result = strtoul("101", NULL, base2);
	failures += check_unsigned_long(result, 5);

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return (failures > 127 || failures < -128) ? 127 : failures;
}
