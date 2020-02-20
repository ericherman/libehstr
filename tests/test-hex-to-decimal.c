/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* test-hex-to-decimal.c */
/* Copyright (C) 2016, 2017, 2019, 2020 Eric Herman <eric@freesa.org> */

#include "../src/ehstr.h"	/* hex_to_decimal */

#include <stdio.h>		/* fprintf */
#include <string.h>		/* strlen */
#include "../submodules/libecheck/src/echeck.h"	/* check_str */

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

int check_hex_to_decimal_bogus(char *in)
{
	char buf[20];
	char *out;
	int failures = 0;

	out = hex_to_decimal(in, strlen(in), buf, 20);
	if (out != NULL) {
		++failures;
		fprintf(stderr, "NULL *not* returned from hex_to_decimal(%s)\n",
			in);
	}
	return failures + check_str(buf, "");
}

int main(void)
{
	int failures;

	failures = 0;

	failures += check_hex_to_decimal("0x00", "0");
	failures += check_hex_to_decimal("0x0113", "275");
	failures += check_hex_to_decimal("0x10007", "65543");
	failures += check_hex_to_decimal("0x7f", "127");
	failures += check_hex_to_decimal("0xFF", "255");
	failures += check_hex_to_decimal_bogus("0xB0G05");

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return check_status(failures);
}
