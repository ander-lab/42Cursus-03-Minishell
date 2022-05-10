# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 15:18:00 by ajimenez          #+#    #+#              #
#    Updated: 2022/05/10 10:25:41 by goliano-         ###   ########.fr        #
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

SRCS	= 	srcs/minishell.c srcs/prompt/prompt.c srcs/lexer/lexer.c srcs/lexer/parser_lexer.c \
			srcs/lexer/second_round.c ./utils/quotes/quotes.c srcs/lexer/token_to_list.c \
			utils/tokens/tokens.c ./utils/str/strings.c ./utils/str/strings2.c ./utils/chequer/chequer.c \
			./utils/lengths/lengths.c srcs/lexer/clean_tokens.c ./utils/handler/error_handler.c \
			./srcs/lexer/init_tokens.c ./srcs/lexer/spaces.c ./srcs/parser/parser.c \
			./srcs/executor/executor.c

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
