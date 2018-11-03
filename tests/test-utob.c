/* test-utob.c
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
#include <stdio.h>
#include <string.h>
#include "echeck.h"
#include <values.h>		/* LONGBITS */

#include "ehstr.h"

int main(void)
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
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return (failures > 127 || failures < -128) ? 127 : failures;
}
