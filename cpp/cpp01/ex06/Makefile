# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 11:35:58 by vspinell          #+#    #+#              #
#    Updated: 2021/11/13 15:21:30 by vspinell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	Karen

SRCS	=	main.cpp \
			Karen.cpp

CXX		=	clang++

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

OBJCS	=	$(SRCS:.cpp=.o)

RM		=	rm -f

%.o	:	%.cpp
		$(CXX) $(CXXFLAGS) -c $<

$(NAME)	:	$(OBJCS)
				$(CXX) -o $(NAME) $(OBJCS)

all				:		$(NAME)

clean			:
						@$(RM) $(OBJCS) *.replace

fclean			:		clean
						@$(RM) $(NAME)

re				:		fclean all

.PHONY			:		all clean fclean re