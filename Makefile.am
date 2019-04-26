#Makefile.am
#Copyright (C) 2016, 2018 Eric Herman <eric@freesa.org>
#
#This work is free software: you can redistribute it and/or modify it
#under the terms of the GNU Lesser General Public License as published by
#the Free Software Foundation, either version 3 of the License, or (at
#your option) any later version.
#
#This work is distributed in the hope that it will be useful, but WITHOUT
#ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
#License for more details.
lib_LTLIBRARIES=libehstr.la
libehstr_la_SOURCES=$(include_HEADERS) src/ehstr.c

include_HEADERS=src/ehstr.h

TESTS=$(check_PROGRAMS)
check_PROGRAMS=\
 test-btou \
 test-decimal-to-hex \
 test-decimal-to-hex-to-dec-loop \
 test-ehstrnlen \
 test-nibbles \
 test-hex-to-decimal \
 test-revstr \
 test-trimstr \
 test-utob

COMMON_TEST_SOURCES=$(include_HEADERS) \
 tests/echeck.h \
 tests/echeck.c

test_btou_SOURCES=$(COMMON_TEST_SOURCES) tests/test-btou.c
test_decimal_to_hex_SOURCES=$(COMMON_TEST_SOURCES) tests/test-decimal-to-hex.c
test_decimal_to_hex_to_dec_loop_SOURCES=$(COMMON_TEST_SOURCES) \
	tests/test-decimal-to-hex-to-dec-loop.c
test_ehstrnlen_SOURCES=$(COMMON_TEST_SOURCES) tests/test-ehstrnlen.c
test_nibbles_SOURCES=$(COMMON_TEST_SOURCES) tests/test-nibbles.c
test_hex_to_decimal_SOURCES=$(COMMON_TEST_SOURCES) tests/test-hex-to-decimal.c
test_revstr_SOURCES=$(COMMON_TEST_SOURCES) tests/test-revstr.c
test_trimstr_SOURCES=$(COMMON_TEST_SOURCES) tests/test-trimstr.c
test_utob_SOURCES=$(COMMON_TEST_SOURCES) tests/test-utob.c

test_btou_LDADD=libehstr.la
test_decimal_to_hex_LDADD=libehstr.la
test_decimal_to_hex_to_dec_loop_LDADD=libehstr.la
test_ehstrnlen_LDADD=libehstr.la
test_hex_to_decimal_LDADD=libehstr.la
test_nibbles_LDADD=libehstr.la
test_revstr_LDADD=libehstr.la
test_trimstr_LDADD=libehstr.la
test_utob_LDADD=libehstr.la


ACLOCAL_AMFLAGS=-I m4 --install

EXTRA_DIST=COPYING COPYING.LESSER

AM_CFLAGS=-std=c89 -O2 -fomit-frame-pointer \
 -ggdb -Wall -Wextra -Wpedantic -Werror \
 -pipe -I./src/

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
	libtool --mode=execute valgrind ./test-nibbles
