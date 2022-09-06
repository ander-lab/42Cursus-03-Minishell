/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:48:53 by goliano-          #+#    #+#             */
/*   Updated: 2022/09/06 11:39:24 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	need_cmd_slash(char *cmd)
{
	int	r;

	if (!cmd)
		return (0);
	r = 1;
	if (cmd[0] == '/' || cmd[0] == '.' || cmd[0] == '~')
		r = 0;
	return (r);
}

int	is_cmd_hide(char *s, int idx, int token)
{
	int		i;
	char	*word;

	if (token <= 0 || token >= 5)
		return (0);
	i = get_cmd_length_until_token(s, idx);
	word = cpy_cmd(s, i, idx);
	return (needs_split(word));
}

int	get_cmd_length_until_token(char *s, int idx)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (s[idx])
	{
		quotes = quote_type(quotes, s, idx);
		if (ft_get_token(s, &idx) != -1 && quotes == 0)
			break ;
		i++;
		idx++;
	}
	return (i);
}

static int	next_is_command(char *word, int idx)
{
	int	is_cmd;

	is_cmd = 0;
	while (word[idx] == ' ')
		idx++;
	if (word[idx] == '\"' || word[idx] == '\'')
		is_cmd = 1;
	return (is_cmd);
}

int	needs_split(char *word)
{
	int	i;
	int	is_in_space;
	int	need_it;
	int	quotes;

	i = 0;
	need_it = 0;
	is_in_space = 0;
	quotes = 0;
	while (word[i] && need_it == 0)
	{
		quotes = quote_type(quotes, word, i);
		if (word[i] == ' ' && quotes == 0)
			is_in_space = 1;
		if (word[i] == ' ' && is_in_space)
			need_it = !next_is_command(word, i);
		if (word[i] != ' ')
			is_in_space = 0;
		i++;
	}
	return (need_it);
}
