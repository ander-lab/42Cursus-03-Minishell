CC	= gcc

CFLAGS	= -Wall -Wextra -Werror #-g3 -fsanitize=address

SRCS =	./srcs/lexer/lexer.c ./srcs/prompt/prompt.c ./srcs/minishell.c ./includes/libft/ft_strlen.c \
	./includes/libft/ft_split.c ./includes/libft/get_next_line.c ./includes/libft/ft_calloc.c \
	./includes/libft/ft_strcpy.c ./includes/libft/ft_substr.c ./includes/libft/ft_strjoin.c \
	./includes/libft/ft_strchr.c ./includes/libft/ft_strdup.c ./includes/libft/ft_memcpy.c \
	./srcs/lexer/parser_lexer.c ./utils/chequer/chequer.c ./utils/lengths/lengths.c \
	./utils/quotes/quotes.c ./utils/str/strings.c ./utils/str/strings2.c ./utils/tokens/tokens.c \
	./includes/libft/ft_strtrim.c ./utils/handler/error_handler.c ./srcs/lexer/clean_tokens.c \
	./includes/libft/ft_putmatrix.c ./includes/libft/ft_putstr_fd.c ./includes/libft/ft_putchar_fd.c \
	./srcs/lexer/token_to_list.c ./includes/libft/ft_lstadd_back_bonus.c \
	./includes/libft/ft_lstlast_bonus.c ./includes/libft/ft_dlstnew_struct.c \
	./includes/libft/ft_dlstadd_back.c ./includes/libft/ft_dlstlast.c ./srcs/lexer/init_tokens.c \
	./srcs/lexer/spaces.c ./srcs/parser/parser.c ./utils/global/count.c ./srcs/executor/executor.c \
	./srcs/lexer/second_round.c ./includes/libft/ft_dlstsize.c ./includes/libft/ft_strncmp.c \
	./utils/files/files.c ./utils/cmd_exec/cmd_exec.c ./utils/forks/forks.c \
	./includes/libft/ft_split_quotes.c ./srcs/builtins/ft_echo.c ./srcs/builtins/ft_env.c \
	./srcs/builtins/ft_exit.c ./srcs/builtins/ft_pwd.c ./includes/libft/ft_iter_str_bool.c \
	./includes/libft/ft_atoi.c ./includes/libft/ft_matrix_data.c ./includes/libft/ft_isdigit.c \
	./includes/libft/ft_matrixlen.c ./includes/libft/ft_max_int.c ./includes/libft/ft_min_int.c \
	./srcs/executor/builtins.c ./srcs/executor/heredoc.c ./srcs/executor/infile.c \
	./srcs/executor/red_app.c ./utils/str/strings3.c ./includes/libft/ft_strjoinnl.c \
	./utils/heredoc/heredoc.c ./utils/heredoc/heredoc2.c ./utils/heredoc/heredoc_cmd.c \
	./includes/libft/ft_putnbr_fd.c

OBJS = $(SRCS:.c=.o)

RM	= rm -f

NAME	= minishell

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS)	-o $(NAME) $(OBJS) -lreadline

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re

