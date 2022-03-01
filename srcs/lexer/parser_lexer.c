/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:02:26 by ajimenez          #+#    #+#             */
/*   Updated: 2022/03/01 13:46:32 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_cmd_str(t_gdata *g_data)
{
	g_data->cmds = ft_calloc(sizeof(char *), (g_data->n_commands + 1));
	if (!g_data->cmds)
		return ;
}

void	custom_split_word(char *word, t_gdata *g_data)
{
	int		l;
	char	*file_name;
	char	*cmd;

	l = 0;
	// LEAK POR AKI jiji
	word = ft_strtrim(word,  " ");
	l = filename_length(word);
	file_name = cpy_cmd(word, l, 0);
	cmd = cpy_cmd2(word, l, length_from_idx(word, l));
	printf("FILE_NAME: %s\n", file_name);
	printf("CMD: %s\n", cmd);
	g_data->cmds[get_cmds_length(g_data)] = file_name;
	g_data->cmds[get_cmds_length(g_data)] = cmd;
}

static void	fill_cmd_str(char *s, int prev_l, int l, t_gdata *g_data)
{
	int		idx;
	char	*word;

	idx = get_cmds_length(g_data);
	word = get_until_token(prev_l, l, s);
	if (g_data->handle_next && needs_split(word))
		custom_split_word(word, g_data);
	else if (exists_word(word))
	{
		g_data->cmds[idx] = word;
		g_data->n_commands--;
	}
	g_data->handle_next = 0;
	if (g_data->last_token > 0 && g_data->last_token < 5)
		g_data->handle_next = 1;
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
		g_data->last_token = ft_get_token(s, &l);
		if (g_data->last_token != -1 && quotes == 0)
		{
			fill_cmd_str(s, prev_l, l, g_data);
			prev_l = l + 1;
		}
	}
	/*if ((g_data->n_commands == 0 || g_data->n_commands == 1 || g_data->n_commands == 2) && !ends_with_token(s))
	{
		printf("get_until_TOKEN: %s\n", get_until_token(prev_l, l, s));
		g_data->cmds[get_cmds_length(g_data)] = get_until_token(prev_l, l, s);
	}*/
	if (!ends_with_token(s))
	{
		char *word;
		word = get_until_token(prev_l, l, s);
		if (g_data->handle_next && needs_split(word))
			custom_split_word(word, g_data);
		else
			g_data->cmds[get_cmds_length(g_data)] = get_until_token(prev_l, l, s);
	}
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
	if (spaces_or_null(s))
		return (0);
	while (s[++i])
	{
		quotes = quote_type(quotes, s, i);
		token = ft_get_token(s, &i);
		if (token != -1 && quotes == 0 && is_cmd_between_tokens(s, i))
		{
			if (is_cmd_hide(s, ++i, token))
				nc++;
			nc++;
		}
	}
	if (starts_with_token(s))
		nc--;
	return (nc);
}
