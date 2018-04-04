m4_define([libmrss_major_version], [0])
m4_define([libmrss_minor_version], [19])
m4_define([libmrss_macro_version], [2])

m4_define([libmrss_version],
          [libmrss_major_version.libmrss_minor_version.libmrss_macro_version])

m4_define([libmrss_version_info],
          [libmrss_minor_version:libmrss_macro_version:libmrss_minor_version])

AC_INIT([libmrss], [libmrss_version])
AC_CONFIG_SRCDIR([src/mrss_generic.c])
AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE
AM_SANITY_CHECK
AM_CONFIG_HEADER(config.h)
AM_MAINTAINER_MODE

AC_PROG_CC
AC_GNU_SOURCE
AC_ISC_POSIX
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AM_PROG_CC_STDC

AC_HEADER_STDC
AC_HEADER_DIRENT

LT_INIT

AC_CHECK_HEADER(curl/curl.h,, AC_MSG_ERROR(libcurl is required to compile libmrss))
AC_CHECK_LIB(curl,curl_version,, AC_MSG_ERROR(libcurl is required to compile libmrss))

PKG_CHECK_MODULES(NXML, nxml >= 0.18 , nxml=yes, nxml=no)

if test "$nxml" = no; then
  AC_MSG_ERROR(libnXML is required to compile libmrss!)
fi

# LOCALE CHECKS...
AC_MSG_CHECKING(for locale enviroment)

AH_TEMPLATE([USE_LOCALE], [Define to 1 if we can use locale])
AH_TEMPLATE([USE_X_LOCALE], [Define to 1 if this is a macosx or xlocale compatible OS])
AH_TEMPLATE([USE_GENERIC_LOCALE], [Define to 1 if this is a generic OS with locale support])

AC_TRY_COMPILE([
  #include <xlocale.h>
  ], [newlocale (LC_ALL_MASK, "C", NULL)],
  x_locale=yes, x_locale=no)

if test "$x_locale" = "yes"; then
  AC_DEFINE(USE_X_LOCALE)
  AC_DEFINE(USE_LOCALE)
  use_locale=yes
fi

AC_TRY_COMPILE([
  #include <locale.h>
  ], [newlocale (LC_ALL_MASK, "C", NULL)],
  generic_locale=yes, generic_locale=no)

if test "$generic_locale" = "yes"; then
  AC_DEFINE(USE_GENERIC_LOCALE)
  AC_DEFINE(USE_LOCALE)
  use_locale=yes
fi

if test "$use_locale" = "yes"; then
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
fi

LDFLAGS="$LDFLAGS $NXML_LIBS"
CFLAGS="$CFLAGS $NXML_CFLAGS -Wall"

AC_SUBST(LIBMRSS_VERSION, [libmrss_version])
AC_SUBST(LIBMRSS_VERSION_INFO, [libmrss_version_info])
AC_SUBST(LIBMRSS_MAJOR_VERSION, [libmrss_major_version])
AC_SUBST(LIBMRSS_MINOR_VERSION, [libmrss_minor_version])
AC_SUBST(LIBMRSS_MICRO_VERSION, [libmrss_macro_version])

AC_OUTPUT([
Makefile
src/mrss.h
src/Makefile
test/Makefile
doc/Makefile
phpmrss/Makefile
mrss.pc
doxy.conf
])

