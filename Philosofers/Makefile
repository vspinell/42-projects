NAME = philo

SRCS =	philo.c utils.c init.c routine.c checker.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(OBJS) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re