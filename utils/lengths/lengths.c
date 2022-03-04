/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lengths.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:29:03 by goliano-          #+#    #+#             */
/*   Updated: 2022/03/04 12:32:53 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	filename_length(char *word)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (word[i])
	{
		quotes = quote_type(quotes, word, i);
		if (word[i] == ' ' && quotes == 0)
			break;
		i++;
	}
	return (i);
}

int	get_cmds_length(t_gdata *g_data)
{
	int	l;

	l = 0;
	while (g_data->cmds[l])
		l++;
	return (l);
}

int	length_from_idx(char *word, int idx)
{
	int	l;

	l = 0;
	while (word[idx])
	{
		idx++;
		l++;
	}
	return (l);
}
