/* test-trimstr.c
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
#include "ehstr.h"		/* trimstr */

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

	return (failures > 127 || failures < -128) ? 127 : failures;
}
