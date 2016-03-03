#ifndef EHSTR_H
#define EHSTR_H

#include <stddef.h>		/* size_t */

/*
  unsigned to big-endian binary
  represents a binary value as a string of zeros and ones
  see also: strtoul(buf, NULL, 2);
*/
char *utob(char *buf, size_t buf_szie, unsigned long val, size_t bits);

/*
  reverse a string in place
  e.g. to convert "0111" from big-endian to little-endian "1110"
*/
void revstr(char *str, size_t buf_size);

/* trim leading and trailing whitespace from a string in place */
void trimstr(char *str, size_t len);

/*
  mostly for c89 compat

  return the length of str, but check only as many as buf_size;
  if a '\0' is not found in the first buf_size, return buf_size
*/
size_t ehstrnlen(const char *str, size_t buf_size);
#if _XOPEN_SOURCE < 700 && _POSIX_C_SOURCE < 200809L
#define strnlen ehstrnlen
#endif

#endif /* EHSTR_H */
