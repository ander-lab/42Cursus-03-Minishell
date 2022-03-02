/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chequer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:48:53 by goliano-          #+#    #+#             */
/*   Updated: 2022/03/02 13:06:37 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_cmd_hide(char *s, int idx, int token)
{
	int		i;
	char	*word;

	if (token <= 0 || token >= 5)
		return (0);
	i = get_cmd_length_until_token(s, idx);
	word = cpy_cmd(s, i, idx);
	word = remove_ind_red(word);
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

int	next_is_command(char *word, int idx)
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

	i = 0;
	need_it = 0;
	is_in_space = 0;
	// LEAK POR AKI jiji
	word = ft_strtrim(word, " ");
	while (word[i] && need_it == 0)
	{
		if (word[i] == ' ' && word[i - 1] == '\\')
			is_in_space = 1;
		if (word[i] == ' ' && word[i - 1] != '\\' && is_in_space == 0)
			need_it = !next_is_command(word, i);
		if (word[i] != ' ')
			is_in_space = 0;
		i++;
	}
	return (need_it);
}
