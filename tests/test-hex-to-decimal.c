
#include "../src/ehstr.h"	/* hex_to_decimal */

#include <stdio.h>		/* fprintf */
#include <string.h>		/* strlen */
#include <echeck.h>		/* check_str */

int check_hex_to_decimal(char *in, char *expected)
{
	char buf[20];
	char *out;

	out = hex_to_decimal(in, strlen(in), buf, 20);
	if (out == NULL) {
		fprintf(stderr, "NULL returned from hex_to_decimal\n");
		return 1;
	}
	return check_str(out, expected);
}

int main(void)
{
	int failures;

	failures = 0;

	failures += check_hex_to_decimal("0x00", "0");
	failures += check_hex_to_decimal("0x0113", "275");
	failures += check_hex_to_decimal("0x10007", "65543");

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return failures;
}
