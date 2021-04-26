NAME: checker.h

SRCS: $(wildcard *.c)
CC :	gcc
CFLAGS: -Wall -Wextra -Werror

OBJ : $(SRCS: .c = .o)

%o	:	%c
$(NAME) :	$(OBJ)
			ar rcs $(NAME) $(OBJ)

all :  $(NAME)

re :	all
		$(CC) $(CFLAGS) main.c $(NAME) -o test
fclean  :       clean
                rm -rf test
                rm -rf ${NAME}

re      :       fclean all

.PHONY  :       all clean fclean re test