#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>

#include "estr.h"

/*
  globals for controlling strictness and errors
*/
unsigned int ESTR_STRICT_UTOB = 0;
unsigned int ESTR_STRICT_BTOU = 0;
unsigned int ESTR_STRICT_STRNLEN = 0;
unsigned int ESTR_STRICT_REVSTR = 0;

/*
  unsigned to binary
  represents a binary value as a string of zeros and ones
*/
char *utob(char *buf, size_t buf_size, unsigned long val, size_t bits)
{
	size_t i, shift, str_pos;

	if (buf_size == 0) {
		fprintf(stderr, "buf_size of 0 is not valid\n");
		if (ESTR_STRICT_UTOB > 1) {
			exit(EXIT_FAILURE);
		} else if (ESTR_STRICT_UTOB > 0) {
			return NULL;
		}
		return buf;
	}
	if (bits == 0) {
		bits = LONGBITS;
	} else if (bits > LONGBITS) {
		fprintf(stderr, "%lu is greater than %lu\n",
			(unsigned long)bits, (unsigned long)LONGBITS);
		if (ESTR_STRICT_UTOB > 1) {
			exit(EXIT_FAILURE);
		}
		bits = LONGBITS;
	}

	str_pos = 0;
	for (i = bits; i > 0; i--) {
		if (str_pos >= (buf_size - 1)) {
			break;
		}
		shift = (i - 1);
		buf[str_pos++] = ((val >> shift) & 1) ? '1' : '0';
	}
	buf[str_pos] = '\0';

	return buf;
}

/*
  binary to unsigned
  convert a string of zeros and ones as a binary value
*/
unsigned long btou(const char *buf, size_t buf_size)
{
	size_t i, j, shift, len;
	unsigned long val, tmp;

	if (buf_size == 0) {
		fprintf(stderr, "buf_size of 0 is not valid\n");
		if (ESTR_STRICT_BTOU) {
			exit(EXIT_FAILURE);
		}
		return 0;
	}

	len = strnlen(buf, buf_size);

	val = buf[0] == '0' ? 0 : ULONG_MAX;

	for (i = 0, j = len; i < len; i++, j--) {
		shift = j - 1;
		if (buf[i] == '0') {
			tmp = ~(1L << shift);
			val &= tmp;
		} else if (buf[i] == '1') {
			tmp = 1L << shift;
			val |= tmp;
		} else {
			fprintf(stderr, "'%s' is not valid\n", buf);
			if (ESTR_STRICT_BTOU) {
				exit(EXIT_FAILURE);
			}
			return 0;
		}
	}
	return val;
}

#if _POSIX_C_SOURCE < 200809L
size_t strnlen(const char *str, size_t buf_size)
{
	size_t len = strlen(str);
	if (len > buf_size) {
		if (ESTR_STRICT_STRNLEN) {
			exit(EXIT_FAILURE);
		}
		return buf_size;
	}
	return len;
}
#endif

void revstr(char *str, size_t buf_size)
{
	size_t i, j, len;
	char swap;

	if (buf_size == 0) {
		if (ESTR_STRICT_REVSTR) {
			exit(EXIT_FAILURE);
		}
		return;
	}

	len = strnlen(str, buf_size);
	for (i = 0, j = len - 1; i < j; i++, j--) {
		swap = str[i];
		str[i] = str[j];
		str[j] = swap;
	}
}

unsigned int set_estr_strict_utob(unsigned int new_val)
{
	unsigned int previous = ESTR_STRICT_UTOB;
	ESTR_STRICT_UTOB = new_val;
	return previous;
}

unsigned int set_estr_strict_btou(unsigned int new_val)
{
	unsigned int previous = ESTR_STRICT_BTOU;
	ESTR_STRICT_BTOU = new_val;
	return previous;
}

unsigned int set_estr_strict_revstr(unsigned int new_val)
{
	unsigned int previous = ESTR_STRICT_REVSTR;
	ESTR_STRICT_REVSTR = new_val;
	return previous;
}

unsigned int set_estr_strict_strnlen(unsigned int new_val)
{
	unsigned int previous = ESTR_STRICT_STRNLEN;
	ESTR_STRICT_STRNLEN = new_val;
	return previous;
}
