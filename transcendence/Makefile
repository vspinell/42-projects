all: up

up:
	@ docker-compose up -d --build

up-f:
	@ docker-compose up -d --build frontend

start:
	@ docker-compose start

stop:
	@ docker-compose stop

clean: stop
	@ docker-compose down -v --remove-orphans

fclean: clean
	@ docker rmi -f $$(docker images -aq)

show_database:
	docker exec server /bin/sh -c "npx prisma studio &"
# open http://localhost:5555/

close_database:
	docker exec server /bin/sh -c "pkill prisma\ studio &"
reload: stop start

re: fclean all

.PHONY: stop clean reload all%
