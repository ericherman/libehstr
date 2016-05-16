#include <stdio.h>
#include <string.h>
#include <echeck.h>
#include <values.h>		/* LONGBITS */

#include "../src/ehstr.h"

int test_revstr(void)
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

int test_trimstr(void)
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

int test_strnlen()
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

int test_utob(void)
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

int test_btou(void)
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

int test_decimal_to_hex()
{
	int failures;
	char buf[20];
	char *rv;
	const char *str;

	failures = 0;

	rv = decimal_to_hex("275", 3, buf, 20);

	if (rv == NULL) {
		fprintf(stderr, "NULL returned from decimal_to_hex\n");
		fprintf(stderr, "Aborting test\n");
		return (1 + failures);
	}

	failures += check_str(buf, "0x0113");

	rv = decimal_to_hex("65543", 10, buf, 20);

	if (rv == NULL) {
		fprintf(stderr, "NULL returned from decimal_to_hex\n");
		fprintf(stderr, "Aborting test\n");
		return (1 + failures);
	}

	failures += check_str(buf, "0x010007");

	str = "5088824049625";
	rv = decimal_to_hex(str, strlen(str), buf, 20);
	if (rv == NULL) {
		fprintf(stderr, "NULL returned from decimal_to_hex\n");
		fprintf(stderr, "Aborting test\n");
		return (1 + failures);
	}
	failures += check_str(buf, "0x04A0D58CBFD9");

	if (failures) {
		fprintf(stderr, "%d failures in test_decimal_to_hex\n",
			failures);
	}

	return failures;
}

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

int test_hex_to_decimal()
{
	int failures;

	failures = 0;

	failures += check_hex_to_decimal("0x00", "0");
	failures += check_hex_to_decimal("0x0113", "275");
	failures += check_hex_to_decimal("0x10007", "65543");

	if (failures) {
		fprintf(stderr, "%d failures in test_hex_to_decimal\n",
			failures);
	}

	return failures;
}

int test_decimal_to_hex_to_decimal_loop()
{
	int failures;
	int i;
	char buf[100];
	char hex[100];
	char dec[100];
	char *numv[] = { "0", "1", "10", "275", "65543", "17", "1025", "106" };
	int numc = 7;

	failures = 0;

	for (i = 0; i < numc; ++i) {
		decimal_to_hex(numv[i], strlen(numv[i]), hex, 100);
		hex_to_decimal(hex, 100, dec, 100);
		failures += check_str(dec, numv[i]);
	}

	/* lets just do a bunch */
	for (i = 1; i < 1000001; i += 25) {
		sprintf(buf, "%d", i);
		decimal_to_hex(buf, strlen(buf), hex, 100);
		hex_to_decimal(hex, 100, dec, 100);
		failures += check_str(dec, buf);
	}

	if (failures) {
		fprintf(stderr, "%d failures in test_hex_to_decimal\n",
			failures);
	}

	return failures;
}

/* int main(int argc, char *argv[]) */
int main(void)
{
	int failures = 0;

	failures += test_revstr();
	failures += test_trimstr();
	failures += test_strnlen();
	failures += test_utob();
	failures += test_btou();
	failures += test_decimal_to_hex();
	failures += test_hex_to_decimal();
	failures += test_decimal_to_hex_to_decimal_loop();

	if (failures) {
		fprintf(stderr, "%d failures in total\n", failures);
	}
	return failures;
}
