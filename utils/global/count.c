/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:54:17 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/11 12:17:45 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_count(char *s)
{
	int	i;
	int	cmd;
	int	quotes;

	i = 0;
	cmd = 1;
	quotes = 0;
	while (s[i])
	{
		quotes = quote_type(quotes, s, i);
		if (s[i] == '|' && quotes == 0)
			cmd++;
		i++;
	}
	return (cmd);
}
