#!/bin/sh
make clean
/usr/local/php/bin/phpize
./configure
make
make install
/usr/local/php/bin/php -m | grep ifeng
/usr/local/php/bin/php test.php
