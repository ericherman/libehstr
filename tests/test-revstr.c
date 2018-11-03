/* test-revstr.c
   Copyright (C) 2016, 2017, 2018 Eric Herman <eric@freesa.org>

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
#include "ehstr.h"		/* revstr */

#include <stdio.h>		/* fprintf */
#include <string.h>		/* strncpy */
#include "echeck.h"		/* check_str */

int check_revstr(const char *in, const char *expected)
{
	char reverse[100];

	reverse[0] = '\0';

	strncpy(reverse, in, 99);

	revstr(reverse, 100);

	return check_str(reverse, expected);
}

int main(void)
{
	int failures;

	failures = 0;
	failures += check_revstr("a", "a");
	failures += check_revstr("ab", "ba");
	failures += check_revstr("edcba", "abcde");
	failures += check_revstr("", "");

	revstr(NULL, 10);

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return (failures > 127 || failures < -128) ? 127 : failures;
}
