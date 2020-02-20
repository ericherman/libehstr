# SPDX-License-Identifier: LGPL-3.0-or-later
# Makefile.am
# Copyright (C) 2016, 2018, 2019, 2020 Eric Herman <eric@freesa.org>

if DEBUG
BUILD_TYPE_CFLAGS=-ggdb -O0 \
	-fno-inline-small-functions \
	-fkeep-inline-functions \
	-fkeep-static-functions \
	--coverage
BUILD_TYPE_LDFLAGS=--coverage
else
BUILD_TYPE_CFLAGS=-ggdb -O2 -DNDEBUG -Wno-unused-parameter -fomit-frame-pointer
BUILD_TYPE_LDFLAGS=
endif

AM_CFLAGS=-std=c89 -Wall -Wextra -Wpedantic -Werror \
 -ggdb $(BUILD_TYPE_CFLAGS) \
 -I./src/ -pipe

AM_LDFLAGS=$(BUILD_TYPE_LDFLAGS)

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
 submodules/libecheck/src/echeck.h \
 submodules/libecheck/src/echeck.c

COMMON_TEST_CFLAGS=-I submodules/libecheck/src

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

test_btou_CFLAGS=$(COMMON_TEST_CFLAGS)
test_decimal_to_hex_CFLAGS=$(COMMON_TEST_CFLAGS)
test_decimal_to_hex_to_dec_loop_CFLAGS=$(COMMON_TEST_CFLAGS)
test_ehstrnlen_CFLAGS=$(COMMON_TEST_CFLAGS)
test_hex_to_decimal_CFLAGS=$(COMMON_TEST_CFLAGS)
test_nibbles_CFLAGS=$(COMMON_TEST_CFLAGS)
test_revstr_CFLAGS=$(COMMON_TEST_CFLAGS)
test_trimstr_CFLAGS=$(COMMON_TEST_CFLAGS)
test_utob_CFLAGS=$(COMMON_TEST_CFLAGS)

ACLOCAL_AMFLAGS=-I m4 --install

EXTRA_DIST=COPYING COPYING.LESSER \
	submodules/libecheck/COPYING \
	submodules/libecheck/COPYING.LESSER \
	submodules/libecheck/src/echeck.h \
	submodules/libecheck/src/echeck.c


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
	pushd submodules/libecheck && \
		rm -rf `cat ../../.gitignore | sed -e 's/#.*//'` \
		rm -rf `cat .gitignore | sed -e 's/#.*//'`; \
		popd


vg-test-btou: test-btou
	./libtool --mode=execute valgrind -q ./test-btou

vg-test-decimal-to-hex: test-decimal-to-hex
	./libtool --mode=execute valgrind -q ./test-decimal-to-hex

vg-test-decimal-to-hex-to-dec-loop: test-decimal-to-hex-to-dec-loop
	./libtool --mode=execute valgrind -q ./test-decimal-to-hex-to-dec-loop

vg-test-ehstrnlen: test-ehstrnlen
	./libtool --mode=execute valgrind -q ./test-ehstrnlen

vg-test-hex-to-decimal: test-hex-to-decimal
	./libtool --mode=execute valgrind -q ./test-hex-to-decimal

vg-test-revstr: test-revstr
	./libtool --mode=execute valgrind -q ./test-revstr

vg-test-trimstr: test-trimstr
	./libtool --mode=execute valgrind -q ./test-trimstr

vg-test-utob: test-utob
	./libtool --mode=execute valgrind -q ./test-utob

vg-test-nibbles: test-nibbles
	./libtool --mode=execute valgrind -q ./test-nibbles


valgrind: vg-test-btou \
	vg-test-decimal-to-hex \
	vg-test-decimal-to-hex-to-dec-loop \
	vg-test-ehstrnlen \
	vg-test-hex-to-decimal \
	vg-test-revstr \
	vg-test-trimstr \
	vg-test-utob \
	vg-test-nibbles
