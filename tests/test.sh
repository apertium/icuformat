#! /usr/bin/env bash

cd $(dirname $0)/locales

genrb -d . root.txt en.txt
echo root.res en.res > package_list.txt
pkgdata -p locales --mode archive -d . package_list.txt

icuformat="./../../src/icuformat"

$icuformat locales.dat simple_message
$icuformat locales.dat complex_message Ahmed 19
