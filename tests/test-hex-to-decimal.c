/* test-hex-to-decimal.c
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

#include "ehstr.h"		/* hex_to_decimal */

#include <stdio.h>		/* fprintf */
#include <string.h>		/* strlen */
#include "echeck.h"		/* check_str */

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

int main(void)
{
	int failures;

	failures = 0;

	failures += check_hex_to_decimal("0x00", "0");
	failures += check_hex_to_decimal("0x0113", "275");
	failures += check_hex_to_decimal("0x10007", "65543");

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return (failures > 127 || failures < -128) ? 127 : failures;
}
