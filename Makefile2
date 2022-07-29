# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/07 17:18:02 by irodrigo          #+#    #+#              #
#    Updated: 2022/07/29 15:25:12 by goliano-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
## proyect configuration
NAME        = minishell
##source routes
HEADERS     =   executer.h minishell.h mshellcmd.h mshellhead.h mshellmsg.h sh_struct.h
SRC			= ./srcs/minishell.c srcs/prompt/prompt.c ./srcs/lexer/lexer.c ./srcs/lexer/parser_lexer.c \
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
			./srcs/builtins/ft_export.c ./srcs/builtins/ft_unset.c                
##auxiliar elements routes
LIBFT_PATH  =   ./includes/libft
GNL_PATH    = 	./includes/libft/get_next_line.c
######include readline flags
#42 system particular instalation
RLINE_FLG_I42 =-L/Users/goliano-/.brew/Cellar/readline/8.1.2/lib
RLINE_INC_I42 =-I/Users/goliano-/.brew/Cellar/readline/8.1.2/include
RLINE_FLG_M42 =-L/Users/mgrau/.brew/Cellar/readline/8.1.2/lib
RLINE_INC_M42 =-I/Users/mgrau/.brew/Cellar/readline/8.1.2/include
#General personal computer instalation
RLINE_FLG = -L/usr/local/opt/readline/lib
RLINE_INC = -I/usr/local/opt/readline/include/
# compiler information
CC = gcc
OTHER = -Wall -Werror -Wextra
CFLAGS = -g3 -lreadline $(OTHER)
# other instructions
RM = rm -f
MAKE = make
.PHONY: clean fclean all re normi
all: $(NAME)
$(NAME): $(SRC)
    @$(MAKE) -C $(LIBFT_PATH)
    @$(CC) $(CFLAGS) $(LIBFT_PATH)/libft.a $(GNL_PATH) $(SRC) -o $(NAME) $(RLINE_FLG_I42) $(RLINE_INC_I42)
    @echo ========= DONE-MAKE-DISASTERSHELL =========
clean:
    @$(MAKE) -C $(LIBFT_PATH) clean
    @echo ========= Clean objects of minishell ====
fclean: clean
    @$(RM) $(NAME)
    @$(MAKE) -C $(LIBFT_PATH) fclean
    @echo ========= FCLEAN-DISASTERSHELL-DONE =======
re: fclean all
normi:
    norminette $(HEADERS) $(SRC) $(BUILTINS)

