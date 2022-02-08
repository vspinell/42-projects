# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fulloa-s <fulloa-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/22 16:32:24 by fulloa-s          #+#    #+#              #
#    Updated: 2021/10/28 13:53:29 by fulloa-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	minishell.c \
				minishell_utils.c \
				signal.c \
				handler_env.c \
				minishell_utils2.c \
				list.c \
				redirs.c \
				redirs2.c \
				matrix_fts.c \
				builtins.c \
				echo.c \
				itoa.c \
				exec_cd.c \
				exec_export.c \
				handler_dollar.c \
				handler_dollar2.c \
				matrix_fts2.c \
				minishell_utils3.c \
				minishell_utils4.c \
				minishell_utils5.c \
				redirs_utils.c \
				redirs_utils2.c \
				redirs2_utils.c \
				credits.c \
				parsing.c \
				pipeline.c
				
NAME		=	minishell

HOMEBREW 	= 	homebrew/opt/readline/lib

CFLAGS		= -Wall -Wextra -Werror

CC			=	gcc

OBJCS		=	$(SRCS:.c=.o)

.c.o		:
				@printf "\033[33m. \x1B[0m"
				@$(CC) $(CFLAGS) -c $<

all			:	clean print run

print		: 	$(HOMEBREW)
				@printf "\r\033[33m[CONVERTING FILES \x1B[0m"

run			:	$(NAME)
			
$(NAME)		:	$(OBJCS)
				@printf "\033[33mdone!]\n"
				@printf "\033[33m[COMPILING MINISHELL ...done!]\n\x1B[0m"
				@$(CC) -o $(NAME) $(OBJCS) -lreadline -I./homebrew/Cellar/readline/8.1.1/include -L./homebrew/Cellar/readline/8.1.1/lib
				@printf "\e[0;32m[DONE! MINISHELL IS READY]\n\x1B[0m"

$(HOMEBREW)	:	
				@printf "\n\e[0;34m[INSTALLING READLINE...]\n\x1B[0m"
				@mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
				@./homebrew/bin/brew install readline
				@printf "\n\e[0;34m[READLINE INSTALLED]\n\n\x1B[0m"


clean		:	
				@echo "\033[33m[CLEANING OBJCS...done!]\x1B[0m"
				@rm -f $(OBJCS)

fclean		:	clean
				@echo "\033[33m[CLEANING MINISHELL...done!]\x1B[0m"
				@echo "\033[33m[CLEANING READLINE...done!]\x1B[0m"
				@rm -rf $(NAME) homebrew

re			:	fclean all

.PHONY		:	all clean fclean re run