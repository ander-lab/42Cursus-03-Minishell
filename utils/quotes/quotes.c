/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:46:46 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/22 14:02:35 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_quote(char c)
{
	int	quotes;

	quotes = 0;
	if (c == '\"')
		quotes = 1;
	if (c == '\'')
		quotes = 2;
	return (quotes);
}

int	is_in_quotes(int quotes, int tquotes)
{
	int	is_in_quotes;

	is_in_quotes = 0;
	if (quotes == 0)
		is_in_quotes = tquotes;
	else if (quotes == tquotes)
		is_in_quotes = 0;
	else
		is_in_quotes = quotes;
	return (is_in_quotes);
}

int	quote_type(int quotes, char *s, int l)
{
	int	quote_type;

	quote_type = quotes;
	if (is_quote(s[l]) == 1)
		quote_type = is_in_quotes(quotes, 1);
	if (is_quote(s[l]) == 2)
		quote_type = is_in_quotes(quotes, 2);
	return (quote_type);
}

int	has_quotes(char *s)
{
	int	i;
	int	quotes;
	int	is_closed;

	i = 0;
	quotes = 0;
	is_closed = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			is_closed = 0;
			if (quotes == 0)
				quotes = is_quote(s[i]);
			else if (quotes == is_quote(s[i]))
				is_closed = 1;
		}
		i++;
	}
	if (is_closed == 0)
		quotes = -1;
	return (quotes);
}
