FROM debian:buster
RUN apt-get update
RUN apt-get install -y wget
RUN apt-get install -y php7.3-fpm php7.3-xml php7.3-mbstring
RUN apt-get install -y php-mysql
RUN apt-get install -y wget

RUN wget https://wordpress.org/latest.tar.gz
RUN tar -xvzf latest.tar.gz && rm -rf latest.tar.gz

RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN chmod +x wp-cli.phar
RUN mv wp-cli.phar /usr/local/bin/wp
RUN wp cli update --yes

#installing adminer
RUN wget https://github.com/vrana/adminer/releases/download/v4.7.3/adminer-4.7.3.php
RUN mv adminer-4.7.3.php adminer.php
RUN mv adminer.php /tmp

RUN mkdir folder
COPY ./srcs/index ./folder/
COPY ./srcs/script.sh ./folder/
COPY ./srcs/start.sh ./folder/
RUN rm wordpress/wp-config-sample.php
ENTRYPOINT bash ./folder/start.sh