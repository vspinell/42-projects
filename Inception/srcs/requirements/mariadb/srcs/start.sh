
./folder/script.sh


if [ ! -d /mariadb/wordpress ];
then

mysql_install_db --user=mysql --datadir='/mariadb'
cat << EOF > /tmp/init.sql
CREATE DATABASE $MYSQL_DATABASE DEFAULT CHARACTER SET utf8;
CREATE USER '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';
GRANT ALL ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';
DELETE FROM mysql.user WHERE User=' ';
ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';
FLUSH PRIVILEGES;
EOF
cd '/usr' ; /usr/bin/mysqld_safe --datadir='/mariadb' --init-file=/tmp/init.sql

else
cd '/usr' ; /usr/bin/mysqld_safe --datadir='/mariadb'

fi