/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_n_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:23:11 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/08 10:51:41 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_n_commands(char *s)
{
	int	i;
	int	nc;
	int	token;
	int	quotes;

	i = -1;
	nc = 1;
	token = 0;
	quotes = 0;
	if (spaces_or_null(s))
		return (0);
	while (s[++i])
	{
		quotes = quote_type(quotes, s, i);
		token = ft_get_token(s, &i);
		if (token != -1 && quotes == 0 && is_cmd_between_tokens(s, i))
		{
			if (is_cmd_hide(s, ++i, token))
				nc++;
			nc++;
		}
	}
	if (starts_with_token(s))
		nc--;
	return (nc);
}
