#ifndef _ESTR_H_
#define _ESTR_H_

#if _POSIX_C_SOURCE < 200809L
size_t strnlen(const char *str, size_t buf_size);
#endif

void revstr(char *str, size_t buf_size);

/*
  unsigned to big-endian binary
  represents a binary value as a string of zeros and ones
*/
char *utob(char *buf, size_t buf_szie, unsigned long val, size_t bits);

/*
  big-endian binary to unsigned
  convert a string of zeros and ones as a binary value
*/
unsigned long btou(const char *buf, size_t buf_size);

#endif /* _ESTR_H_ */
