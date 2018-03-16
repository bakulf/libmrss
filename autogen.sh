#!/bin/bash

aclocal
libtoolize
autoheader
autoconf
automake --add-missing
