/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:02:26 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/12 14:47:33 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_cmd_str(t_gdata *g_data, int i)
{
	if (i > 0)
		ft_free_matrix(g_data->cmds);
	g_data->cmds = ft_calloc(sizeof(char *), (g_data->n_commands + 1));
	if (!g_data->cmds)
		return ;
}

// TODO -> LEAK POR AKI jiji
void	custom_split_word(char *word, t_gdata *g_data)
{
	int		l;
	char	*file_name;
	char	*cmd;
	char	*trim;

	l = 0;
	trim = ft_strtrim(word, " ");
	l = filename_length(trim);
	file_name = cpy_cmd(trim, l, 0);
	cmd = cpy_cmd2(trim, l, length_from_idx(trim, l));
	g_data->cmds[get_cmds_length(g_data)] = ft_strtrim(file_name, " ");
	g_data->cmds[get_cmds_length(g_data)] = ft_strtrim(cmd, " ");
	free(trim);
	free(file_name);
	free(cmd);
}

static void	fill_cmd_str(char *s, int prev_l, int l, t_gdata *g_data)
{
	char	*word;

	word = get_until_token(prev_l, l, s);
	if (g_data->handle_next && needs_split(word))
	{
		custom_split_word(word, g_data);
		g_data->aux_n_commands--;
	}
	else if (exists_word(word))
	{
		g_data->cmds[get_cmds_length(g_data)] = ft_strtrim(word, " ");
		g_data->aux_n_commands--;
	}
	g_data->handle_next = 0;
	if (is_file_token(g_data->last_token))
		g_data->handle_next = 1;
	free(word);
}

void	fill_cmds_word(char *s, t_gdata *gdata, int prev_l, int l)
{
	char	*word;

	if (!ends_with_token(s))
	{
		word = get_until_token(prev_l, l, s);
		if (gdata->handle_next && needs_split(word))
			custom_split_word(word, gdata);
		else
			gdata->cmds[get_cmds_length(gdata)] = ft_strtrim(word, " ");
		free(word);
	}
}

void	handle_input(char *s, t_gdata *g_data, int i)
{
	int		prev_l;
	int		l;
	int		quotes;

	l = -1;
	prev_l = 0;
	quotes = 0;
	init_cmd_str(g_data, i);
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
	fill_cmds_word(s, g_data, prev_l, l);
	g_data->err = quotes;
}
