FROM debian:stretch

RUN mkdir ./folder
COPY ./tools/* ./folder

RUN apt-get update
RUN apt-get install -y nginx
RUN apt-get install -y openssl

COPY ./nginx.conf /etc/nginx/
RUN ./folder/autoindex_on.sh
RUN openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes -out /etc/ssl/pino.pem -keyout /etc/ssl/pino.key -subj "/C=IT/ST=Rome/L=Rome/O=42RomaLuiss/OU=vspinell/CN=localhost"

EXPOSE 443

ENTRYPOINT bash /folder/start.sh