/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:23:54 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/20 12:34:02 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	strquotes_len(char *cmd)
{
	int	qt;
	int	fq;
	int	i;
	int	l;
	int	lq;

	fq = 0;
	qt = 0;
	i = -1;
	l = 0;
	lq = 0;
	while (cmd[++i])
	{
		qt = is_quote(cmd[i]);
		if (qt > 0 && fq == 0)
			fq = qt;
		else if (qt == fq && fq != 0)
			lq = 1;
		else if (qt == fq)
			fq = 0;
		if ((fq != qt || qt == 0) && lq == 0)
			l++;
		lq = 0;
	}
	return (l);
}

static char	*quote_copy(char *str, char *new)
{
	int	qt;
	int	fq;
	int	lq;
	int	i;
	int	x;

	fq = 0;
	lq = 0;
	i = -1;
	x = -1;
	while (str[++i])
	{
		qt = is_quote(str[i]);
		if (qt > 0 && fq == 0)
			fq = qt;
		else if (qt == fq && fq != 0)
			lq = 1;
		else if (qt == fq)
			fq = 0;
		if ((fq != qt || qt == 0) && lq == 0)
			new[++x] = str[i];
	}
	return (new);
}

char	*remove_quotes(char *cmd)
{
	char	*new;

	if (!cmd)
		return (cmd);
	new = ft_calloc(sizeof(char), ft_strlen(cmd) + 1);
	if (!new)
		return (0);
	new = quote_copy(cmd, new);
	free(cmd);
	return (new);
}
