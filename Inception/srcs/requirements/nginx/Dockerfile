FROM debian:buster

RUN mkdir folder
COPY ./tools/*.sh ./folder/
COPY ./tools/conf ./folder/

RUN apt-get update
RUN apt-get install -y nginx
RUN apt-get install -y openssl

RUN mv ./folder/conf /etc/nginx/nginx.conf
RUN ./folder/autoindex_on.sh
RUN openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes -out /etc/ssl/pino.pem -keyout /etc/ssl/pino.key -subj "/C=IT/ST=Rome/L=Rome/O=42RomaLuiss/OU=vspinell/CN=localhost"
