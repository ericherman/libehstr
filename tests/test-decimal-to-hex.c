/* test-decimal-to-hex.c
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
#include "../src/ehstr.h"	/* decimal_to_hex */

#include <stdio.h>		/* fprintf */
#include "echeck.h"		/* check_str */
#include <string.h>		/* strlen */

int main(void)
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

	str = "200";
	rv = decimal_to_hex(str, strlen(str), buf, 20);
	if (rv == NULL) {
		fprintf(stderr, "NULL returned from decimal_to_hex\n");
		fprintf(stderr, "Aborting test\n");
		return (1 + failures);
	}
	failures += check_str(buf, "0x00C8");

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return check_status(failures);
}
