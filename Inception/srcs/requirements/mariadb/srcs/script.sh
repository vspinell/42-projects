#!/bin/bash

SOURCE=/etc/mysql/mariadb.conf.d/50-server.cnf

SEARCH="127.0.0.1"
REPLACE="0.0.0.0"

sed -i "s/$SEARCH/$REPLACE/" $SOURCE