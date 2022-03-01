/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:47:49 by goliano-          #+#    #+#             */
/*   Updated: 2022/02/24 16:02:04 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cpy_cmd(char *s, int l, int idx)
{
	char	*word;
	int		x;
	int		aux;

	word = ft_calloc(sizeof(char), (l + 1));
	if (!word)
		return (0);
	x = 0;
	aux = idx;
	idx += l;
	while (aux < idx)
	{
		word[x] = s[aux];
		aux++;
		x++;
	}
	return (word);
}

char	*cpy_cmd2(char *s, int fl, int l)
{
	int		i;
	char	*cmd;
	//int		aux;

	i = 0;
	cmd = ft_calloc(sizeof(char), (l + 1));
	if (!cmd)
		return (0);
	//aux = l - fl;
	while (s[fl])
	{
		cmd[i] = s[fl];
		fl++;
		i++;
	}
	return (cmd);
}


