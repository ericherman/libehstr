/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* test-utob.c */
/* Copyright (C) 2016, 2017, 2019 Eric Herman <eric@freesa.org> */

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
