/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* test-revstr.c */
/* Copyright (C) 2016, 2017, 2018, 2019 Eric Herman <eric@freesa.org> */

#include "../src/ehstr.h"	/* revstr */

#include <stdio.h>		/* fprintf */
#include <string.h>		/* strncpy */
#include "echeck.h"		/* check_str */

int check_revstr(const char *in, const char *expected)
{
	char reverse[100];

	reverse[0] = '\0';

	strncpy(reverse, in, 99);

	revstr(reverse, 100);

	return check_str_m(reverse, expected, in);
}

int main(void)
{
	int failures;

	failures = 0;
	failures += check_revstr("a", "a");
	failures += check_revstr("ab", "ba");
	failures += check_revstr("edcba", "abcde");
	failures += check_revstr("", "");

	revstr(NULL, 10);

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return check_status(failures);
}
