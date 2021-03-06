/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* test-ehstr-strnlen.c */
/* Copyright (C) 2016, 2017, 2019 Eric Herman <eric@freesa.org> */

#include "../src/ehstr.h"	/* eembed_strnlen */

#include <stdio.h>		/* fprintf */
#include "../submodules/libecheck/src/echeck.h"	/* check_unsigned_int */
#include <string.h>		/* perhaps strnlen */

int main()
{
	int failures = 0;
	char *foo = "foo";

	failures += check_unsigned_int(3, eembed_strnlen(foo, 100));
	failures += check_unsigned_int(2, eembed_strnlen(foo, 2));

	failures +=
	    check_unsigned_int(strnlen(foo, 100), eembed_strnlen(foo, 100));
	failures += check_unsigned_int(strnlen(foo, 2), eembed_strnlen(foo, 2));

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return check_status(failures);
}
