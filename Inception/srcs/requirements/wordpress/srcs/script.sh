#!/bin/bash

# Assign the filename
filename="/etc/php/7.3/fpm/pool.d/www.conf"

# Take the search string
search="\/run\/php\/php7.3-fpm.sock"
replace="9000;"

if [[ $search != "" && $replace != "" ]]; then
sed -i "s/$search/$replace/" $filename
fi
