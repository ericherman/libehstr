#include <stdio.h>
#include <string.h>
#include <echeck.h>
#include <values.h>		/* LONGBITS */

#include "ehstr.h"

int check_revstr(void)
{
	int failures;
	char expected[10], reverse[10];

	failures = 0;
	strncpy(expected, "edcba", 10);
	strncpy(reverse, "abcde", 10);

	revstr(reverse, 10);

	failures += check_str(reverse, expected);
	if (failures) {
		fprintf(stderr, "%d failures in check_revstr\n", failures);
	}

	return failures;
}

int check_trimstr(void)
{
	int failures;
	char expected[20], actual[20];

	failures = 0;

	strncpy(expected, "foo AND bar -> baz", 20);
	strncpy(actual, "foo AND bar -> baz\n", 20);
	trimstr(actual, 20);
	failures += check_str(actual, expected);

	strncpy(expected, "foo AND bar", 20);
	strncpy(actual, " \tfoo AND bar \n", 20);
	trimstr(actual, 20);
	failures += check_str(actual, expected);

	if (failures) {
		fprintf(stderr, "%d failures in check_trimstr\n", failures);
	}

	return failures;
}

int check_strnlen()
{
	int failures = 0;
	char *foo = "foo";

	failures += check_unsigned_int(3, strnlen(foo, 100));
	failures += check_unsigned_int(2, strnlen(foo, 2));

	if (failures) {
		fprintf(stderr, "%d failures in check_strnlen\n", failures);
	}
	return failures;
}

int check_utob(void)
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
		fprintf(stderr, "%d failures in check_utob\n", failures);
	}
	return failures;
}

int check_btou(void)
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
		fprintf(stderr, "%d failures in check_btou\n", failures);
	}
	return failures;
}

/* int main(int argc, char *argv[]) */
int main(void)
{
	int failures = 0;

	failures += check_revstr();
	failures += check_trimstr();
	failures += check_strnlen();
	failures += check_utob();
	failures += check_btou();

	if (failures) {
		fprintf(stderr, "%d failures in total\n", failures);
	}
	return failures;
}
