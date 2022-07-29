# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 15:18:00 by ajimenez          #+#    #+#              #
#    Updated: 2022/07/29 13:28:57 by goliano-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
# 									 PROGRAM                                   #
# **************************************************************************** #

NAME 	= minishell
INCLUDE = ./includes/minishell.h
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

SRCS	= 	./srcs/minishell.c srcs/prompt/prompt.c ./srcs/lexer/lexer.c ./srcs/lexer/parser_lexer.c \
			./srcs/lexer/second_round.c ./utils/quotes/quotes.c ./srcs/lexer/token_to_list.c \
			./utils/tokens/tokens.c ./utils/str/strings.c ./utils/str/strings2.c ./utils/chequer/chequer.c \
			./utils/lengths/lengths.c ./srcs/lexer/clean_tokens.c ./utils/handler/error_handler.c \
			./srcs/lexer/init_tokens.c ./srcs/lexer/spaces.c ./utils/global/count.c \
			./srcs/executor/executor.c ./utils/forks/forks.c ./utils/cmd_exec/cmd_exec.c \
			./srcs/executor/infile.c ./utils/heredoc/heredoc2.c ./utils/files/files.c \
			./srcs/executor/heredoc.c ./utils/str/strings3.c ./utils/heredoc/heredoc.c \
			./utils/list/list.c ./utils/cmds/cmds.c ./srcs/lexer/cmds_lst.c \
			./srcs/parser/parser.c ./srcs/executor/builtins.c ./srcs/builtins/ft_echo.c \
			./srcs/builtins/ft_env.c ./srcs/builtins/ft_exit.c ./srcs/builtins/ft_pwd.c \
			./srcs/builtins/ft_export.c ./srcs/builtins/ft_unset.c #./includes/minishell.h

# **************************************************************************** #
# 								    RULES                                      #
# **************************************************************************** #

RLINE_FLG_I42 =-L/Users/goliano-/.brew/Cellar/readline/8.1.2/lib
RLINE_INC_I42 =-I/Users/goliano-/.brew/Cellar/readline/8.1.2/include
READ_IN	= -I/Users/$(USER)/.brew/Cellar/readline/include
READ_L	= -lreadline -L /Users/$(USER)/.brew/Cellar/readline/lib

F_RL = -I ~/.brew/opt/readline/include -I ~/.brew/opt/readline/lib    
F_RL2 = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include

OBJS	= $(SRCS:.c=.o)
COMP	= $(CC) $(CFLAGS) $(LIBP) $(SRCS) -o $(NAME) -lreadline	$(F_RL) $(F_RL2) #$(READ_IN) $(READ_L) #$(RLINE_FLG_I42) $(RLINE_INC_I42)
SANCOMP	= $(CC) $(CFLAGS) $(SAN) $(LIBP) $(SRCS) -g3 -o $(NAME) -lreadline $(F_RL) $(F_RL2)#$(READ_IN) $(READ_L) #$(RLINE_FLG_I42) $(RLINE_INC_I42)

all: 		$(NAME)

$(NAME):			$(OBJS) #$(INCLUDE)
					@echo "\n\033[33mMaking libft! ░░░░░░ (._.)\ ░░░░░\033[39m\n"
					@make bonus -s -C ./includes/libft
					@cp includes/libft/libft.a ./$(LIBP)
					$(CC) $(CFLAGS) $(LIB) $(LIBP) $(OBJS)
					$(COMP) 
					@echo "\n\033[1;32mEverything done! ░░░░░░ ＼(>o<)ノ ░░░░░\033[39m\n"

fsanitize:			$(OBJS) #$(INCLUDE)
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
