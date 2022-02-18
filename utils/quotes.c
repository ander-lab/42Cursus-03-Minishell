/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:46:46 by goliano-          #+#    #+#             */
/*   Updated: 2022/02/18 18:06:03 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_quote(char c)
{
	int	quotes;

	quotes = 0;
	if (c == '\"')
		quotes = 1;
	if (c == '\'')
		quotes = 2;
	return (quotes);
}

int is_in_quotes(int quotes, int tquotes)
{
	int is_in_quotes;

	is_in_quotes = 0;
	if (quotes == 0)
		is_in_quotes = tquotes;
	else if (quotes == tquotes)
		is_in_quotes = 0;
	else
		is_in_quotes = quotes;
	return (is_in_quotes);
}
