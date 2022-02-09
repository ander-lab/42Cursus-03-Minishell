# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 13:31:58 by ajimenez          #+#    #+#              #
#    Updated: 2022/02/09 15:03:35 by ajimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 									 PROGRAM                                   #
# **************************************************************************** #

NAME 	= minishell
LIBP	= minishell.a 
# **************************************************************************** #
# 									COMPILER                                   #
# **************************************************************************** #

CC		= gcc 
CFLAGS	= -Wall -Wextra -Werror
SAN		= -fsanitize=address
LIB 	= ar -rcs
RM		= /bin/rm -rf

# **************************************************************************** #
# 									INCLUDES                                   #
# **************************************************************************** #

LIBFT	= ./includes/libft/libft.a

# **************************************************************************** #
# 									SOURCES                                    #
# **************************************************************************** #

SRCS	= srcs/minishell.c srcs/prompt/prompt.c srcs/lexer/lexer.c

# **************************************************************************** #
# 								    RULES                                      #
# **************************************************************************** #

OBJS	= $(SRCS:.c=.o)
COMP	= $(CC) $(CFLAGS) $(LIBP) $(SRCS) -o $(NAME) -lreadline
SANCOMP	= $(CC) $(CFLAGS) $(SAN) $(LIBP) $(SRCS) -g3 -o $(NAME) -lreadline

all: 		$(NAME)

$(NAME):			$(OBJS)
					@echo "\n\033[33mMaking libft! ░░░░░░ (._.)\ ░░░░░\033[39m\n"
					@make bonus -s -C ./includes/libft
					@cp includes/libft/libft.a ./$(LIBP)
					$(LIB) $(LIBP) $(OBJS)
					$(COMP) 
					@echo "\n\033[1;32mEverything done! ░░░░░░ ＼(>o<)ノ ░░░░░\033[39m\n"

fsanitize:			$(OBJS)
					@echo "\n\033[33mMaking libft! ░░░░░░ /(ಠ_ಠ)\ ░░░░░\033[39m\n"
					@make bonus -s -C ./includes/libft
					@cp includes/libft/libft.a ./$(LIBP)
					$(LIB) $(LIBP) $(OBJS)
					$(SANCOMP)
					@echo "\n\033[1;32mEverything done! ░░░░░░ ＼(>o<)ノ ░░░░░\033[39m\n"

clean:
					@make clean -C ./includes/libft
					$(RM) $(OBJS) $(OBJS_B)

fclean: 	clean
					@make fclean -C ./includes/libft
					$(RM) $(NAME)
					$(RM) $(PROG)
					$(RM) $(LIBP)
					@echo "\n\033[31mEverything fcleaned! ░░░░░░ ٩(╬ʘ益ʘ╬)۶ ░░░░░\n\033[39m"

re:			fclean all

.PHONY: all clean fclean reincludes
