/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:54:17 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/31 15:11:31 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_count(char *s)
{
	int	i;
	int	cmd;
	int	quotes;
	int	token;

	i = 0;
	cmd = 1;
	quotes = 0;
	token = 0;
	while (s[i])
	{
		quotes = quote_type(quotes, s, i);
		token = ft_get_token(s, &i);
		if ((token == 0 || token == 3) && quotes == 0)
			cmd++;
		i++;
	}
	return (cmd);
}
