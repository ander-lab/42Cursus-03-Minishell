/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:02:26 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/22 15:55:26 by goliano-         ###   ########.fr       */
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

int		needs_split(char *word, t_gdata *g_data)
{
	int	i;
	int	need_it;

	i = 0;
	need_it = 0;
	g_data->handle_next = 0;
	// LEAK POR AKI jiji
	word = ft_strtrim(word,  " ");
	while (word[i] && need_it == 0)
	{
		if (word[i] == ' ' && word[i - 1] != '\\')
			need_it = 1;
		i++;
	}
	return (need_it);
}

void	custom_split_word(char *word, t_gdata *g_data)
{
	int		l;
	char	*file_name;
	char	*cmd;

	l = 0;
	printf("WORD: %s\n", word);
	// LEAK POR AKI jiji
	word = ft_strtrim(word,  " ");
	while (word[l])
	{
		l++;
		if (word[l] == ' ' && word[l - 1] != '\\')
			break;
	}
	printf("L: %d\n", l);
	printf("N_COMMANDS2: %d\n", g_data->n_commands);
	file_name = malloc(sizeof(char) * (l + 1));
	if (!file_name)
		return ;
	//ft_strlcpy(file_name, word, l);
	int	i = 0;
	while (i < l)
	{
		file_name[i] = word[i];
		printf("NAMEN: %d\n", file_name[i]);
		printf("NAMEC: %c\n", file_name[i]);
		i++;
	}
	file_name[i] = '\0';
	int	r = 0;
	int	nl = 0;
	while (word[l])
	{
		nl++;
		l++;
	}
	cmd = malloc(sizeof(char) * (nl + 1));
	if (!cmd)
		return ;
	int aux = l - nl;
	while (word[aux])
	{
		cmd[r] = word[aux];
		r++;
		aux++;
	}
	cmd[r] = '\0';
	printf("CMD: %s\n", cmd);
	printf("FILE_NAME: %s\n", file_name);
	g_data->cmds[get_cmds_length(g_data)] = file_name;
	g_data->cmds[get_cmds_length(g_data)] = cmd;
}

static void	fill_cmd_str(char *s, int prev_l, int l, t_gdata *g_data)
{
	int	idx;
	char	*word;

	idx = get_cmds_length(g_data);
	word = get_until_token(prev_l, l, s);
	if (g_data->handle_next && needs_split(word, g_data))
		custom_split_word(word, g_data);
	else if (exists_word(word))
	{
		g_data->cmds[idx] = word;
		g_data->n_commands--;
	}
	if (g_data->last_token > 0 && g_data->last_token < 5)
	{
		printf("ENTRO CON TOKEN: %d\n", g_data->last_token);
		g_data->handle_next = 1;
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
		g_data->last_token = ft_get_token(s, &l);
		if (g_data->last_token != -1 && quotes == 0)
		{
			fill_cmd_str(s, prev_l, l, g_data);
			prev_l = l + 1;
		}
	}
	if ((g_data->n_commands == 0 || g_data->n_commands == 1) && !ends_with_token(s))
	{
		printf("g_DATA: %d\n", g_data->handle_next);
		printf("get_until: %s\n", get_until_token(prev_l, l, s));
		g_data->cmds[get_cmds_length(g_data)] = get_until_token(prev_l, l, s);
	}
	g_data->data_error = quotes;
}

/*int	is_cmd_hide(char *s, int idx)
{
	int	i;
	int	token;

	i = 0;
	token = ft_get_token(s, &idx);
	if (token != -1)
		idx++;
	printf("TOKEN: %d\n", token);
	while (s[idx])
	{
		printf("S[idx]: %c\n", s[idx]);
		idx++;
	}
	return (idx);
}*/

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
		token = ft_get_token(s, &i);
		if (token != -1 && quotes == 0 && is_cmd_between_tokens(s, i))
		{
//			is_cmd_hide(s, i);
			nc++;
		}
	}
	if (starts_with_token(s))
		nc--;
	return (nc);
}
