lib_LTLIBRARIES=libehstr.la
libehstr_la_SOURCES=src/ehstr.c

include_HEADERS=src/ehstr.h

TESTS=$(check_PROGRAMS)
check_PROGRAMS=test-ehstr
test_ehstr_SOURCES=tests/test-ehstr.c src/ehstr.h
test_ehstr_LDADD=libehstr.la -lecheck

ACLOCAL_AMFLAGS=-I m4 --install

AM_CFLAGS=-std=c89 -O3 -ggdb -Wall -Wextra -Wpedantic -Werror

# extracted from https://github.com/torvalds/linux/blob/master/scripts/Lindent
LINDENT=indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0

tidy:
	$(LINDENT) \
		-T FILE \
		-T size_t \
		*.h *.c

spotless:
	rm -rf `cat .gitignore`
