/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* test-btou.c */
/* Copyright (C) 2016, 2017, 2019 Eric Herman <eric@freesa.org> */

#include "../src/ehstr.h"	/* nothing */

#include <stdio.h>		/* fprintf */
#include <stdlib.h>		/* strtol strtoul */
#include "../submodules/libecheck/src/echeck.h"	/* check_long check_unsigned_long */

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

	return check_status(failures);
}
