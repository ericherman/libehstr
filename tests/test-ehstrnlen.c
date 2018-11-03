/* test-ehstrnlen.c
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
#include "ehstr.h"		/* ehstrnlen */

#include <stdio.h>		/* fprintf */
#include "echeck.h"		/* check_unsigned_int */
#include <string.h>		/* perhaps strnlen */

int main()
{
	int failures = 0;
	char *foo = "foo";

	failures += check_unsigned_int(3, ehstrnlen(foo, 100));
	failures += check_unsigned_int(2, ehstrnlen(foo, 2));

	failures += check_unsigned_int(strnlen(foo, 100), ehstrnlen(foo, 100));
	failures += check_unsigned_int(strnlen(foo, 2), ehstrnlen(foo, 2));

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return (failures > 127 || failures < -128) ? 127 : failures;
}
