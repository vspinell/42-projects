FROM debian:buster
RUN apt-get update
RUN apt upgrade -y

RUN mkdir folder
RUN apt-get install -y mariadb-server procps

COPY ./srcs/start.sh ./folder/
COPY ./srcs/script.sh ./folder/

RUN mkdir -p maridb

ENTRYPOINT bash ./folder/start.sh