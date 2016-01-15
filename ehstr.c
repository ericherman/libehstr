#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>

#include "ehstr.h"

char *utob(char *buf, size_t buf_size, unsigned long val, size_t bits)
{
	size_t i, shift, str_pos;

	if (buf_size == 0) {
		return buf;
	}

	if (bits == 0 || bits > LONGBITS) {
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

unsigned long btou(const char *buf, size_t buf_size)
{
	size_t i, j, shift, len;
	unsigned long val, tmp;

	if (buf_size == 0) {
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
			break;
		}
	}
	return val;
}

#if _XOPEN_SOURCE < 700 && _POSIX_C_SOURCE < 200809L
size_t strnlen(const char *str, size_t buf_size)
{
	size_t i;

	for (i = 0; i < buf_size; ++i) {
		if (*(str + i) == '\0') {
			return i;
		}
	}

	return buf_size;
}
#endif

void revstr(char *str, size_t buf_size)
{
	size_t i, j, len;
	char swap;

	len = strnlen(str, buf_size);
	for (i = 0, j = len - 1; i < j; i++, j--) {
		swap = str[i];
		str[i] = str[j];
		str[j] = swap;
	}
}
