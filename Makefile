# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 15:18:00 by ajimenez          #+#    #+#              #
#    Updated: 2022/09/20 14:16:55 by ajimenez         ###   ########.fr        #
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
#CFLAGS	= -Wall -Wextra -Werror
SAN		= -fsanitize=address -g3
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
			./srcs/lexer/init_tokens.c ./srcs/lexer/spaces.c ./utils/global/count.c \
			./srcs/executor/executor.c ./utils/forks/forks.c ./utils/cmd_exec/cmd_exec.c \
			./srcs/executor/infile.c ./utils/heredoc/heredoc2.c ./utils/files/files.c \
			./srcs/executor/heredoc.c ./utils/str/strings3.c ./utils/heredoc/heredoc.c \
			./utils/list/list.c ./utils/cmds/cmds.c ./srcs/lexer/cmds_lst.c \
			./srcs/parser/parser.c ./srcs/executor/builtins.c ./srcs/builtins/ft_echo.c \
			./srcs/builtins/ft_env.c ./srcs/builtins/ft_exit.c ./srcs/builtins/ft_pwd.c \
			./srcs/builtins/ft_export.c ./srcs/builtins/ft_unset.c ./srcs/builtins/utils.c ./srcs/builtins/ft_cd.c \
			./utils/builtins/echo.c ./utils/signals/signals.c ./srcs/env/init_env.c \
			./utils/builtins/global.c ./utils/forks/handle_cmd.c  \
			./utils/builtins/envp_to_lst.c ./utils/builtins/ft_dup_var.c \
			./utils/builtins/ft_strjoin_token.c ./utils/builtins/get_env_line.c \
			./utils/builtins/lst_to_envmtrx.c ./utils/builtins/safe_getcwd.c \
			./utils/expansion/get_env_val.c ./srcs/executor/expansion.c ./utils/expansion/quotes.c \
			./srcs/lexer/get_n_commands.c srcs/lexer/init_cmds_lst.c utils/cmd_exec/smart_split.c \
			./utils/free/free.c ./srcs/lexer/get_cmd.c ./utils/builtins/init_cd.c

# **************************************************************************** #
# 								    RULES                                      #
# **************************************************************************** #

OBJS	= $(SRCS:.c=.o)
RL_LIB	= -L /Users/$(USER)/.brew/opt/readline/lib
RL_INC	= -I/Users/$(USER)/.brew/opt/readline/include
COMP	= $(CC) $(CFLAGS) $(LIBP) $(SRCS) -lreadline $(RL_LIB) $(RL_INC) -o $(NAME)
SANCOMP	= $(CC) $(CFLAGS) $(SAN) $(LIBP) $(SRCS) -g3 -lreadline $(RL_LIB) $(RL_INC) -o $(NAME)

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
