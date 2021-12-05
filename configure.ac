# SPDX-License-Identifier: LGPL-3.0-or-later
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libehstr], [2.1.0], [eric@freesa.org])
AC_CONFIG_SRCDIR([src/ehstr.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AC_USE_SYSTEM_EXTENSIONS

# Checks for programs.
AC_PROG_CC
AC_PROG_LN_S

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stddef.h string.h values.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_STRNLEN
AC_CHECK_FUNCS([strtol strtoul])

# Add an --enable-debug option in a somewhat horrible and non-autotoolsy way
AC_ARG_ENABLE(debug,
	AS_HELP_STRING([--enable-debug],
		[enable debugging, default: no]),
	[case "${enableval}" in
		yes) debug=true ;;
		no)  debug=false ;;
		*)   AC_MSG_ERROR(\
			[bad value ${enableval} for --enable-debug]) ;;
	 esac],
	[debug=false])
AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

AC_ARG_ENABLE(faux-freestanding,
	AS_HELP_STRING([--enable-faux-freestanding],
		[enable functions to support freestanding, default: no]),
	[case "${enableval}" in
		yes) faux_freestanding=true ;;
		no)  faux_freestanding=false ;;
		*)   AC_MSG_ERROR(\
		    [bad value ${enableval} for --enable-faux-freestanding]) ;;
	 esac],
	[faux_freestanding=false])
AM_CONDITIONAL(FAUX_FREESTANDING, test x"$faux_freestanding" = x"true")

AM_INIT_AUTOMAKE([subdir-objects -Werror -Wall])
AM_PROG_AR
LT_INIT

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
