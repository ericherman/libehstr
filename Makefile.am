lib_LTLIBRARIES=libehstr.la
libehstr_la_SOURCES=src/ehstr.c

include_HEADERS=src/ehstr.h

TESTS=$(check_PROGRAMS)
check_PROGRAMS=\
 test-btou \
 test-decimal-to-hex \
 test-decimal-to-hex-to-dec-loop \
 test-ehstrnlen \
 test-hex-to-decimal \
 test-revstr \
 test-trimstr \
 test-utob

test_btou_SOURCES=tests/test-btou.c src/ehstr.h
test_decimal_to_hex_SOURCES=src/ehstr.h tests/test-decimal-to-hex.c
test_decimal_to_hex_to_dec_loop_SOURCES=src/ehstr.h \
	tests/test-decimal-to-hex-to-dec-loop.c
test_ehstrnlen_SOURCES=src/ehstr.h tests/test-ehstrnlen.c
test_hex_to_decimal_SOURCES=src/ehstr.h tests/test-hex-to-decimal.c
test_revstr_SOURCES=src/ehstr.h tests/test-revstr.c
test_trimstr_SOURCES=src/ehstr.h tests/test-trimstr.c
test_utob_SOURCES=src/ehstr.h tests/test-utob.c

test_btou_LDADD=libehstr.la -lecheck
test_decimal_to_hex_LDADD=libehstr.la -lecheck
test_decimal_to_hex_to_dec_loop_LDADD=libehstr.la -lecheck
test_ehstrnlen_LDADD=libehstr.la -lecheck
test_hex_to_decimal_LDADD=libehstr.la -lecheck
test_revstr_LDADD=libehstr.la -lecheck
test_trimstr_LDADD=libehstr.la -lecheck
test_utob_LDADD=libehstr.la -lecheck


ACLOCAL_AMFLAGS=-I m4 --install

EXTRA_DIST=misc

AM_CFLAGS=-std=c89 -O3 -ggdb -Wall -Wextra -Wpedantic -Werror

# extracted from https://github.com/torvalds/linux/blob/master/scripts/Lindent
LINDENT=indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0

tidy:
	$(LINDENT) \
		-T FILE \
		-T size_t \
		`find src tests -name '*.h' -o -name '*.c'`

spotless: clean
	rm -rf `cat .gitignore`
	pushd src && rm -rf `cat ../.gitignore | sed -e 's/#.*//'`; popd
	pushd tests && rm -rf `cat ../.gitignore | sed -e 's/#.*//'`; popd

valgrind: $(check_PROGRAMS)
	libtool --mode=execute valgrind ./test-btou
	libtool --mode=execute valgrind ./test-decimal-to-hex
	libtool --mode=execute valgrind ./test-decimal-to-hex-to-dec-loop
	libtool --mode=execute valgrind ./test-ehstrnlen
	libtool --mode=execute valgrind ./test-hex-to-decimal
	libtool --mode=execute valgrind ./test-revstr
	libtool --mode=execute valgrind ./test-trimstr
	libtool --mode=execute valgrind ./test-utob
