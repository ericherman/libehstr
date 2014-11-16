#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>

#include "estr.h"

/*
  unsigned to binary
  represents a binary value as a string of zeros and ones
*/
char *utob(char *buf, size_t buf_size, unsigned long val, size_t bits)
{
	size_t i, shift, str_pos;

	if (buf_size == 0) {
		fprintf(stderr, "buf_size of 0 is not valid\n");
#ifdef ESTR_STRICT_UTOB
		exit(EXIT_FAILURE);
#elif ESTR_SEMI_STRICT_UTOB
		return NULL;
#else
		return buf;
#endif
	}
	if (bits == 0) {
		bits = LONGBITS;
	} else if (bits > LONGBITS) {
		fprintf(stderr, "%lu is greater than %lu\n",
			(unsigned long)bits, (unsigned long)LONGBITS);
#ifdef ESTR_STRICT_UTOB
		exit(EXIT_FAILURE);
#endif
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
#ifdef ESTR_STRICT_BTOU
		exit(EXIT_FAILURE);
#else
		return 0;
#endif
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
#ifdef ESTR_STRICT_BTOU
			exit(EXIT_FAILURE);
#else
			return 0;
#endif
		}
	}
	return val;
}

#if _POSIX_C_SOURCE < 200809L
size_t strnlen(const char *str, size_t buf_size)
{
	size_t len = strlen(str);
	if (len > buf_size) {
#ifdef ESTR_STRICT_STRNLEN
		exit(EXIT_FAILURE);
#else
		return buf_size;
#endif
	}
	return len;
}
#endif

void revstr(char *str, size_t buf_size)
{
	size_t i, j, len;
	char swap;

	if (buf_size == 0) {
#ifdef ESTR_STRICT_REVSTR
		exit(EXIT_FAILURE);
#else
		return;
#endif
	}

	len = strnlen(str, buf_size);
	for (i = 0, j = len - 1; i < j; i++, j--) {
		swap = str[i];
		str[i] = str[j];
		str[j] = swap;
	}
}
