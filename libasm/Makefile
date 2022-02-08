NAME	=	libasm.a

SRCS	=	${wildcard srcs/*.s}

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

OBJ		=	${SRCS:.s=.o}

%.o		:	%.s
			nasm -f macho64 $<

$(NAME)	:	${OBJ}
			ar rcs ${NAME} ${OBJ}

all		:	$(NAME)

test	:	all
			$(CC) $(CFLAGS) main.c $(NAME) -o test

clean	:
			rm -rf ${OBJ}

fclean	:	clean
			rm -rf test
			rm -rf ft_write.res
			rm -rf ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re test
