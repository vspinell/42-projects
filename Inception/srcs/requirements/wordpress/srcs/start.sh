./folder/script.sh
mkdir -p /var/www
mkdir -p /var/www/html


if [ ! -d /var/www/html/wordpress ]; then
mv wordpress /var/www/html/
mv	/tmp/adminer.php /var/www/html/

mv /folder/assets syte
mv /folder/css syte
mv /folder/js syte
mv /folder/index.html syte
mv syte /var/www/html

sleep 15
wp config create --allow-root --dbname=$WORDPRESS_DB_NAME --dbuser=$WORDPRESS_DB_USER --dbpass=$WORDPRESS_DB_PASSWORD --dbhost=$WORDPRESS_DB_HOST  --skip-check --path=$WORDPRESS_PATH
wp core install --allow-root --url=https://localhost/wordpress --title=$WORDPRESS_DB_NAME --admin_user=vspinell --admin_password=$WORDPRESS_DB_PASSWORD --admin_email=blabe@blabe.com --path=$WORDPRESS_PATH
wp user create --allow-root $WORDPRESS_USER_LOGIN $WORDPRESS_USER_MAIL --user_pass=$WORDPRESS_USER_PASSWD --role=$WORDPRESS_USER_ROLE --path=$WORDPRESS_PATH
wp plugin --allow-root install redis-cache --activate --path=$WORDPRESS_PATH
wp plugin activate redis-cache --path=$WORDPRESS_PATH --allow-root
sed -i "56 i define('WP_REDIS_HOST', 'redis');" /var/www/html/wordpress/wp-config.php
wp redis --allow-root enable --path=$WORDPRESS_PATH
fi

service php7.3-fpm start
service php7.3-fpm stop

#php -a
php-fpm7.3 --nodaemonize
