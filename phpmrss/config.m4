PHP_ARG_WITH(mrss,          for MRSS support,
[  --with-mrss=DIR        Include MRSS support where DIR is MRSS install
                          prefix. If DIR is not set, the bundled MRSS library
                          will be used.])

PHP_ARG_ENABLE(mrss, Support for mrss,
[  --enable-mrss           Enable mrss support])

if test "$PHP_MRSS" = "yes"; then

  for i in $with_mrss /usr/local /usr; do
    if test -f $i/lib/libmrss.$SHLIB_SUFFIX_NAME -o -f $i/lib/libmrss.a; then
      MRSS_DIR=$i
    fi
  done

  if test -z "$MRSS_DIR"; then
    AC_MSG_ERROR("Please reinstall mrss distribution. libmrss.(a|so) not found.)
  fi

  if test -f $MRSS_DIR/include/mrss.h; then
    MRSS_INC_DIR=$MRSS_DIR/include
  fi

  if test -z "$MRSS_INC_DIR"; then
    AC_MSG_ERROR("Please reinstall mrss distribution. mrss.h not found.)
  fi

  PHP_CHECK_LIBRARY(mrss, mrss_parse_url, [
      AC_DEFINE(HAVE_MRSS, 1, [ ])
    ],[
      AC_MSG_ERROR([LiBOX library required.])
    ], [
      -L$MRSS_DIR/lib
    ]
   )

  PHP_ADD_INCLUDE($MRSS_INC_DIR)
  PHP_ADD_LIBRARY_WITH_PATH(mrss, $MRSS_DIR/lib, MRSS_SHARED_LIBADD) 

  PHP_NEW_EXTENSION(mrss, php.c, $ext_shared)
  PHP_SUBST(MRSS_SHARED_LIBADD)
fi
