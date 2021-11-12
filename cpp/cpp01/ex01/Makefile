# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/12 11:35:58 by vspinell          #+#    #+#              #
#    Updated: 2021/11/12 17:54:31 by vspinell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	MoarBrainz

SRCS	=	main.cpp \
			Zombie.cpp \
			ZombieHorde.cpp 


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
						@$(RM) $(OBJCS)

fclean			:		clean
						@$(RM) $(NAME)

re				:		fclean all

.PHONY			:		all clean fclean re