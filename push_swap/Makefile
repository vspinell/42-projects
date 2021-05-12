NAME = checker

NAME2 = push_swap

SRCS =  checker.c \
		commands.c \
		ft_split.c \
		main.c \
		utils.c \
		utils2.c \
		parsing.c

SRCS2 =  push_swap.c \
		commands2.c \
		utilsP.c \
		utils2P.c \
		utils3P.c \
		utils4P.c \
		subsequence.c \
		ft_split.c \
		best_move.c \
		best_move2.c \
		main2.c \
		parsing2.c

OBJS = $(SRCS:.c=.o)

OBJS2 = $(SRCS2:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: 		$(NAME) $(NAME2)

$(NAME): 	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(NAME2): 	$(OBJS2)
			$(CC) $(CFLAGS) -o $(NAME2) $(OBJS2)

clean:
			$(RM) $(OBJS) $(OBJS2)

fclean: 	clean
			$(RM) $(OBJS) $(OBJS2) $(NAME) $(NAME2)

re: 		fclean all

.PHONY: 	all clean fclean re