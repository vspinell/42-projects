# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 16:46:02 by fulloa-s          #+#    #+#              #
#    Updated: 2022/02/08 13:05:30 by fulloa-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		ft_containers

SRCS			=		main.cpp \

CXX				=		clang++

CXXFLAGS		=		-Wall -Wextra -Werror -std=c++98

OBJCS			=		$(SRCS:.cpp=.o)

RM				=		rm -f

%.o				: 		%.cpp
						@$(CXX) $(CXXFLAGS) -c $<

$(NAME)			:		$(OBJCS)
						@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJCS)

all				:		$(NAME)
						@./ft_containers
						

test			:		all
						@$(RM) $(OBJCS)
						@make NAME="std_containers" CXXFLAGS="-Wall -Wextra -Werror -std=c++98  -D STD"
						@./std_containers
						@vimdiff myFT.txt mySTL.txt

clean			:
						@$(RM) $(OBJCS)

fclean			:		clean
						@$(RM) $(NAME) std_containers
						@$(RM) mySTL.txt myFT.txt 
						

re				:		fclean all

.PHONY			:		all clean fclean re
