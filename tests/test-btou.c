/* test-btou.c
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
#include "../src/ehstr.h"	/* nothing */

#include <stdio.h>		/* fprintf */
#include <stdlib.h>		/* strtol strtoul */
#include "echeck.h"		/* check_long check_unsigned_long */

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
