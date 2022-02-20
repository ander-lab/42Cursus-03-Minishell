/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:02:26 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/18 18:11:43 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_cmd_str(t_gdata *g_data)
{
	g_data->cmds = ft_calloc(sizeof(char *), (g_data->n_commands + 1));
	if (!g_data->cmds)
		return ;
}

static int	get_cmds_length(t_gdata *g_data)
{
	int	l;

	l = 0;
	while (g_data->cmds[l])
		l++;
	return (l);
}

static void	fill_cmd_str(char *s, int prev_l, int l, t_gdata *g_data)
{
	int	idx;
	char	*word;

	idx = get_cmds_length(g_data);
	word = get_until_token(prev_l, l, s);
	if (exists_word(word))
	{
		g_data->cmds[idx] = word;
		g_data->n_commands--;
	}
}

void	handle_input(char *s, t_gdata *g_data)
{
	int		prev_l;
	int		l;
	int		quotes;

	l = -1;
	prev_l = 0;
	quotes = 0;
	init_cmd_str(g_data);
	while (s[++l])
	{
		quotes = quote_type(quotes, s, l);
		if (ft_get_token(s, l) != -1 && quotes == 0)
		{
			fill_cmd_str(s, prev_l, l, g_data);
			prev_l = l + 1;
		}
	}
	if ((g_data->n_commands == 0 || g_data->n_commands == 1) && !ends_with_token(s))
		g_data->cmds[get_cmds_length(g_data)] = get_until_token(prev_l, l, s);
	g_data->data_error = quotes;
}

int	get_n_commands(char *s)
{
	int	i;
	int	nc;
	int	token;
	int	quotes;

	i = -1;
	nc = 1;
	token = 0;
	quotes = 0;
	while (s[++i])
	{
		quotes = quote_type(quotes, s, i);
		token = ft_get_token(s, i);
		if (token != -1 && quotes == 0 && is_cmd_between_tokens(s, i))
			nc++;
	}
	if (starts_with_token(s))
		nc--;
	return (nc);
}
