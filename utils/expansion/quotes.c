/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:23:54 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/21 17:40:48 by ajimenez         ###   ########.fr       */
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

static int	quote_copy(char c)
{
	int 	qt;
	int 	fq;
	int 	lq;

	fq = 0;
	lq = 0;
	qt = is_quote(c);
	if (qt > 0 && fq == 0)
		fq = qt;
	else if (qt == fq && fq != 0)
		lq = 1;
	else if (qt == fq)
		fq = 0;
	if ((fq != qt || qt == 0) && lq == 0)
		return (1);
	return (0);
}

char	*remove_quotes(char *cmd)
{
	int		i;
	int		x;
	char	*new;
		
	i = 0;
	x = -1;
	if (!cmd)
		return (cmd);
	new = ft_calloc(sizeof(char), ft_strlen(cmd) + 1);
	if (!new)
		return (0);
	while (cmd[i])
	{
		if (quote_copy(cmd[i]))
			new[++x] = cmd[i];
		i++;
	}
	free(cmd);
	return (new);
}
