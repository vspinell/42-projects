#!/bin/sh

sudo -- sh -c -e "echo '127.0.0.1	vspinell.42.fr' >> /etc/hosts";
cd /home/vspinell && mkdir data
cd /home/vspinell/data && mkdir db_data

