# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 19:39:28 by vspinell          #+#    #+#              #
#    Updated: 2021/11/26 15:23:54 by vspinell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		AMateria

SRCS			=		main.cpp \
						Cure.cpp \
						Ice.cpp \
						Character.cpp \
						AMateria.cpp \
						MateriaSource.cpp

CXX				=		clang++

CXXFLAGS		=		-Wall -Wextra -Werror -std=c++98

OBJCS			=		$(SRCS:.cpp=.o)

RM				=		rm -f

%.o				: 		%.cpp
						@$(CXX) $(CXXFLAGS) -c $<

$(NAME)			:		$(OBJCS)
						@$(CXX) -o $(NAME) $(OBJCS)

all				:		$(NAME)

clean			:
						@$(RM) $(OBJCS)

fclean			:		clean
						@$(RM) $(NAME) 

re				:		fclean all

.PHONY			:		all clean fclean re
