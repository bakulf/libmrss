#!/bin/sh

set -e

aclocal
libtoolize
autoheader
autoconf
automake --add-missing --foreign
