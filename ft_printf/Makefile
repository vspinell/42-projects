# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-gius <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 15:14:19 by mde-gius          #+#    #+#              #
#    Updated: 2021/02/23 13:53:14 by vspinell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  ft_printf.c	\
			utils.c		\
			ft_computlen.c	\
			utils2.c		\
			ft_format.c		\
			ft_typeprocess.c \
			ft_printf.c \
			reminders.c \
			reminders2.c

OBJS	=	${SRCS:.c=.o}
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
NAME	=	libftprintf.a
AR		=	ar -rcs

.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
$(NAME)	:	${OBJS}
			${AR} $(NAME) $(OBJS)
all		:	$(NAME)
clean 	:
			rm -rf $(OBJS)
fclean : 	clean
			rm -rf $(NAME)

re : fclean all
.PHONY : all clean fclean re
