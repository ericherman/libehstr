/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* test-trimstr.c */
/* Copyright (C) 2016, 2017, 2019 Eric Herman <eric@freesa.org> */

#include "../src/ehstr.h"	/* trimstr */

#include <stdio.h>		/* fprintf */
#include <string.h>		/* strncpy */
#include "echeck.h"		/* check_str */

int main(void)
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
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return check_status(failures);
}
