#!/bin/bash

function check {
  if ! test $1 = "0"; then
    echo " error."
    exit
  fi
}

echo -n "Creating a work directory... "
rm -rf /tmp/phpmrss > /dev/null
check $?
mkdir /tmp/phpmrss > /dev/null
check $?
cp -r * /tmp/phpmrss > /dev/null
check $?
cd /tmp/phpmrss > /dev/null
check $?
echo " done."

echo -n "Checking data with phpize... "
phpize > /dev/null
check $?
echo " done."

echo -n "Configuring... "
./configure > /dev/null
check $?
echo " done."

echo -n "Compiling... "
make > /dev/null
check $?
echo " done."

echo -n "Installing... "
make install > /dev/null
check $?
echo " done."

echo -n "Removing work directory... "
rm -rf /tmp/phpmrss > /dev/null
check $?
echo " done."

# bye :)
