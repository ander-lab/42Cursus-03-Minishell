/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:47:49 by goliano-          #+#    #+#             */
/*   Updated: 2022/02/23 15:47:12 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

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
