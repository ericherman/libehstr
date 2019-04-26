/* test-decimal-to-hex-to-dec-loop.c
   Copyright (C) 2016, 2017 Eric Herman <eric@freesa.org>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

	https://www.gnu.org/licenses/lgpl-3.0.txt
	https://www.gnu.org/licenses/gpl-3.0.txt
 */
#include "../src/ehstr.h"	/* decimal_to_hex hex_to_decimal */

#include <stdio.h>		/* fprintf */
#include <string.h>		/* strlen */
#include "echeck.h"		/* check_str */

int main(void)
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
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return check_status(failures);
}
