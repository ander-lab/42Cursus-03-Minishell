/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:17:40 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/18 11:27:55 by ajimenez         ###   ########.fr       */
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

void 	lexer_lst(t_list *token_lst);
int		ft_give_token(char c1, char c2, int *aux);
char	*get_until_token(int prev_l, int l, char *str);
int		is_escaping(char c);
void	handle_input(char *str, t_gdata *g_data/*, t_token_data *cmd_table*/);
int		get_n_commands(char *s);
int		get_n_tokens(char *s);
int		is_quote(char c);
int		is_in_quotes(int quotes, int tquotes);

#endif
