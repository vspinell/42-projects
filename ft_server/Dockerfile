#installing the OS
FROM debian:buster

RUN mkdir ./folder
COPY ./srcs/* ./folder

#installing all the pacages needed to run the sewrvices
RUN apt-get update
RUN apt-get install -y nginx
RUN apt-get install -y wget
RUN apt-get install -y mariadb-server
RUN apt-get install -y php7.3-fpm php7.3-xml php7.3-mbstring
RUN apt-get install -y openssl
RUN apt-get install -y php-mysql

#installing and unzipping wordpress and phpmyadmin from web
RUN wget https://files.phpmyadmin.net/phpMyAdmin/5.1.0/phpMyAdmin-5.1.0-english.tar.gz
RUN tar -xvzf phpMyAdmin-5.1.0-english.tar.gz && rm -rf phpMyAdmin-5.1.0-english.tar.gz
RUN mv phpMyAdmin-5.1.0-english /var/www/html/phpmyadmin
RUN wget https://wordpress.org/latest.tar.gz
RUN tar -xvzf latest.tar.gz && rm -rf latest.tar.gz
RUN mv wordpress /var/www/html/

#copying the modified configuration files into the unzipped folders
COPY ./srcs/index.nginx-debian.html /var/www/html
COPY ./srcs/config.inc.php /var/www/html/phpmyadmin
COPY /srcs/wp-config.php /var/www/html/wordpress

#creating ssl certificate and ssl key
RUN openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes -out /etc/ssl/pino.pem -keyout /etc/ssl/pino.key -subj "/C=IT/ST=Rome/L=Rome/O=42RomaLuiss/OU=vspinell/CN=localhost"

#changing nginx configurazion file
RUN ./folder/autoindex_off.sh

#ownership privileges
RUN chown -R www-data:www-data /var/www/html/*
RUN chmod -R 755 /var/www/html/*

#creating a new database
RUN service mysql start && mysql -u root < /folder/wordpress.sql

#alllowing the ports to listen
EXPOSE 80
EXPOSE 443

ENTRYPOINT bash /folder/start.sh
