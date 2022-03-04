/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:47:49 by goliano-          #+#    #+#             */
/*   Updated: 2022/03/04 12:21:02 by goliano-         ###   ########.fr       */
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

	i = 0;
	cmd = ft_calloc(sizeof(char), (l + 1));
	if (!cmd)
		return (0);
	while (s[fl])
	{
		cmd[i] = s[fl];
		fl++;
		i++;
	}
	return (cmd);
}


char	*pretty_hostname(char *str)
{
	char	*word;
	int		i;

	word = ft_calloc(sizeof(char), (ft_strlen(str) + 4));
	if (!word)
		return (0);
	ft_strcpy(word, str);
	i = ft_strlen(str);
	word[i] = ':';
	word[i + 1] = ' ';
	word[i + 2] = '\0';
	free(str);
	return (word);
}

char	*add_at_sign(char *str)
{
	char	*word;
	int		i;

	word = ft_calloc(sizeof(char), (ft_strlen(str) + 2));
	if (!word)
		return (0);
	ft_strcpy(word, str);
	i = ft_strlen(str);
	word[i] = '@';
	word[i + 1] = '\0';
	free(str);
	return (word);
}
