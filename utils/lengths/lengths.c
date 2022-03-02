/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lengths.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:29:03 by goliano-          #+#    #+#             */
/*   Updated: 2022/03/02 13:06:46 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	filename_length(char *word)
{
	int	i;
	int	is_in_space;

	i = 0;
	is_in_space = 0;
	while (word[i])
	{
		if (word[i] == ' ' && word[i - 1] == '\\')
			is_in_space = 1;
		if (word[i] == ' ' && word[i - 1] != '\\' && is_in_space == 0)
			break ;
		if (word[i] != ' ')
			is_in_space = 0;
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
