/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:53:22 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/31 14:11:14 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_token(char *s, int *raw_tokens, int i, int l)
{
	if (s[i] == ' ')
		raw_tokens[l] = -3;
	else
		raw_tokens[l] = -1;
}

void	handle_token(int *quotes, int *token, char *s, int *i)
{
		*quotes = quote_type(*quotes, s, *i);
		*token = ft_get_token(s, i);
}

static int	put_tokens_on_arr(char *s, int *raw_tokens)
{
	int	i;
	int	l;
	int	token;
	int	quotes;
	int	r;

	i = -1;
	l = 0;
	quotes = 0;
	while (s[++i])
	{	
		handle_token(&quotes, &token, s, &i);
		if (token != -1 && quotes == 0)
		{
			raw_tokens[l] = token;
			r = i;
			if (is_cmd_hide(s, ++i, token))
				raw_tokens[++l] = -2;
			i = r;
		}
		else
			write_token(s, raw_tokens, i, l);
		l++;
	}
	return (l);
}

void	init_tokens(char *s, t_gdata *gdata)
{
	int				raw_len;
	int				*raw_tokens;
	t_dlist			*token_lst;
	t_token_data	*token_data;
	int				*clean_tkns;

	token_data = ft_calloc(sizeof(t_token_data), 1);
	raw_tokens = ft_calloc(sizeof(int), ft_strlen(s) + 1);
	token_lst = NULL;
	raw_len = put_tokens_on_arr(s, raw_tokens);
	clean_tkns = clean_tokens(raw_tokens, raw_len, \
			gdata->n_commands + gdata->n_tokens);
	ft_insert_data_lst(&token_lst, token_data, clean_tkns, \
			gdata->n_commands + gdata->n_tokens);
	ft_convert_matrix(gdata->cmds, token_lst);
	clean_lst_tokens(token_lst);
	gdata->glob_lst = token_lst;
	init_cmds_lst(gdata);
	free(raw_tokens);
	free(clean_tkns);
}
