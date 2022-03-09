/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:17:40 by ajimenez          #+#    #+#             */
/*   Updated: 2022/03/07 11:08:10 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "./libft/libft.h"
# include "structs_and_macros.h"

void	init_prompt(t_gdata *g_data, char **envp);
void 	lexer(char *s, t_gdata *g_data);

int	*clean_tokens(int *raw, int raw_len, int len);
//int		*clean_tokens(int *raw, int raw_len, int len, int n_commands);

void	clean_lst_tokens(t_dlist *token_lst);
int		ft_give_token(char c1, char c2, int *aux);
char	*get_until_token(int prev_l, int l, char *str);
int		is_escaping(char c);
void	handle_input(char *str, t_gdata *g_data/*, t_token_data *cmd_table*/);
int		get_n_commands(char *s);
int		is_file_token(int t);

/*
 * QUOTES
 */
int		is_quote(char c);
int		is_in_quotes(int quotes, int tquotes);
int     quote_type(int quotes, char *s, int l);

/*  
 * TOKENS 
 */
int		ft_get_token(char *s, int *l);
int		ft_give_token(char c1, char c2, int *aux);
int		ends_with_token(char *s);
int		starts_with_token(char *s);
int		get_n_tokens(char *s);

/*
 * STR
 */
char	*remove_ind_red(char *s);
int		exists_word(char *s);
int		is_cmd_between_tokens(char *s, int idx);
char	*get_until_token(int prev_l, int l, char *str);
int		spaces_or_null(char *s);

/*
 * STR 2
 */
char	*cpy_cmd(char *s, int l, int idx);
char	*cpy_cmd2(char *s, int fl, int l);
char	*pretty_hostname(char *str);
char	*add_at_sign(char *str);

/*
 * CHEQUER
 */
int		needs_split(char *word);
int		get_cmd_length_until_token(char *s, int idx);
int		is_cmd_hide(char *s, int idx, int token);

/*
 * LENGTHS
 */
int		length_from_idx(char *word, int idx);
int		get_cmds_length(t_gdata *g_data);
int		filename_length(char *word);

/*
 *	HANDLER
 */
void	no_cmds_handler(char *s);
//t_list	*ft_lstnew_struct(void *newcontent, size_t size);
void	ft_insert_data_lst(t_dlist **lst, t_token_data *token_data, int *tokens, int len);
void	ft_convert_matrix(char **words, t_dlist *lst);

#endif
