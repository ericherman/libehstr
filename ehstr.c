#include <values.h>		/* LONGBITS */
#include <ctype.h>		/* isspace */

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

size_t ehstrnlen(const char *str, size_t buf_size)
{
	size_t i;

	for (i = 0; i < buf_size; ++i) {
		if (*(str + i) == '\0') {
			return i;
		}
	}

	return buf_size;
}

void trimstr(char *str, size_t buf_size)
{
	size_t i, j, offset, len, nonwhite;

	len = (str && buf_size) ? strnlen(str, buf_size) : 0;
	if (len == 0) {
		return;
	}

	nonwhite = 0;
	for (i = 0; i < len && isspace(str[i]); ++i) ;
	offset = i;

	if (offset) {
		for (i = 0, j = offset; j < len; ++i, ++j) {
			str[i] = str[j];
			if (isspace(str[i]) == 0) {
				nonwhite = i;
			}
		}
		if (nonwhite + 1 < len) {
			str[nonwhite + 1] = '\0';
		}
		return;
	}

	nonwhite = 0;
	for (i = len; i > 0 && nonwhite == 0; --i) {
		if (isspace(str[i - 1])) {
			str[i - 1] = '\0';
		} else {
			nonwhite = 1;
		}
	}
}

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
