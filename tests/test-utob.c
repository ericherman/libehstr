#include <stdio.h>
#include <string.h>
#include <echeck.h>
#include <values.h>		/* LONGBITS */

#include "../src/ehstr.h"

int main(void)
{
	int failures;
	char buf[LONGBITS + 1];
	size_t bits;

	failures = 0;

	bits = 4;
	utob(buf, LONGBITS + 1, 5, bits);
	failures += check_str("0101", buf);

	bits = 3;
	utob(buf, LONGBITS + 1, 5, bits);
	failures += check_str("101", buf);

	bits = 8;
	utob(buf, LONGBITS + 1, -3, bits);
	failures += check_str("11111101", buf);

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return (failures > 127 || failures < -128) ? 127 : failures;
}