FROM debian:buster

RUN apt-get update
RUN apt upgrade -y
RUN apt-get install -y redis-server ftp
RUN mkdir folder
COPY srcs/redis.conf ./folder
COPY srcs/start.sh ./folder
ENTRYPOINT ./folder/start.sh
