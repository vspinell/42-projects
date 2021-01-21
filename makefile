# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vspinell <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 16:49:28 by vspinell          #+#    #+#              #
#    Updated: 2021/01/17 15:00:28 by vspinell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# DECLARATIONS:
SRCS = ${wildcard *.c}
OBJS		=	${SRCS:.c=.o}
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
NAME		=	libft.a
AR			=	ar -rcs
.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
$(NAME):	${OBJS}
			${AR} $(NAME) $(OBJS)
all:		$(NAME)
clean:
			rm -f ${OBJS}
fclean:		clean
			rm -f ${NAME}
re:			fclean all
.PHONY: 	all clean fclean re
