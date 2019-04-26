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

#include "../src/ehstr.h"

int main(void)
{
	int failures;
	unsigned char byte, out;
	char high, low;

	failures = 0;
	high = '\0';
	low = '\0';

	byte = 0x00;
	byte_to_hex_chars(byte, &high, &low);
	failures += check_char(high, '0');
	failures += check_char(low, '0');
	out = hex_chars_to_byte(high, low);
	failures += check_unsigned_int(out, byte);

	byte = 0xA3;
	byte_to_hex_chars(byte, &high, &low);
	failures += check_char(high, 'A');
	failures += check_char(low, '3');
	out = hex_chars_to_byte(high, low);
	failures += check_unsigned_int(out, byte);

	byte = 0x0b;
	byte_to_hex_chars(byte, &high, &low);
	failures += check_char(high, '0');
	failures += check_char(low, 'B');
	out = hex_chars_to_byte(high, low);
	failures += check_unsigned_int(out, byte);

	if (failures) {
		fprintf(stderr, "%d failures in %s\n", failures, __FILE__);
	}

	return check_status(failures);
}
