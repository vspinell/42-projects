NAME = inception
START_PATH = ./srcs/

all: setup start

setup:
	@ cd ./srcs/requirements/tools && sudo bash script_hosts.sh
	
stop:
	@ cd $(START_PATH) && sudo docker-compose down;

volumes:
	@ sudo docker volume rm $$(sudo docker volume ls -q)

clean: stop volumes
	@ cd $(START_PATH) &&  sudo docker system prune -a -f;

purge: clean
	@ sudo rm -Rf ~/data/;

start:
	@ cd $(START_PATH) &&  sudo docker-compose up -d; 
re: purge all

.PHONY: setup stop clean purge reload all
