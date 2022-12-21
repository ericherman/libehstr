/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* test-trimstr.c */
/* Copyright (C) 2016, 2017, 2019, 2020 Eric Herman <eric@freesa.org> */

#include "../src/ehstr.h"	/* trimstr */

#include <stdio.h>		/* fprintf */
#include <string.h>		/* strncpy */
#include "../submodules/libecheck/src/echeck.h"	/* check_str */

unsigned check_trimstr(const char *in, const char *expected)
{
	char msg[50];
	char actual[30];

	eembed_assert(strlen(in) < sizeof(actual));
	eembed_assert(strlen(expected) < (sizeof(msg)-10));

	eembed_strncpy(actual, in, sizeof(actual));

	msg[0] = '\0';
	eembed_strncat(msg, "in: \"", sizeof(msg));
	eembed_strncat(msg, in, sizeof(msg));
	eembed_strncat(msg, "\"", sizeof(msg));

	trimstr(actual, sizeof(actual));

	return check_str_m(actual, expected, msg);
}

int main(void)
{
	int failures;
	char expected[20], actual[20];

	failures = 0;

	failures += check_trimstr("", "");
	failures += check_trimstr(" ", "");
	failures += check_trimstr("\t \n", "");
	failures += check_trimstr("a b c", "a b c");
	failures += check_trimstr("  foo AND bar", "foo AND bar");
	failures += check_trimstr("foo AND bar -> baz\n", "foo AND bar -> baz");
	failures += check_trimstr(" \tfoo AND bar \n", "foo AND bar");

	strncpy(expected, "foo AND bar -> baz", 20);
	strncpy(actual, "foo AND bar -> baz\n", 20);
	chomp_crlf(actual, 20);
	failures += check_str(actual, expected);

	strncpy(expected, " \tfoo AND bar ", 20);
	strncpy(actual, " \tfoo AND bar \n", 20);
	chomp_crlf(actual, 20);
	failures += check_str(actual, expected);

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return check_status(failures);
}
