/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:32:11 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/04 12:26:07 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	split_in_quotes(char c, int quotes)
{
	if (is_quote(c))
	{
		if (quotes == is_quote(c))
			quotes = 0;
		else if (quotes == 0)
			quotes = is_quote(c);
	}
	return (quotes);
}

static int	count_words(char const *str, char c)
{
	size_t	trigger;
	int		count;
	int		quotes;

	count = 0;
	quotes = 0;
	if (str[0] && str[0] != c)
		count++;
	trigger = 0;
	while (trigger < ft_strlen(str))
	{
		quotes = split_in_quotes(str[trigger], quotes);
		if (quotes == 0 && str[trigger] == c && str[trigger + 1] && str[trigger + 1] != c)
			count++;
		trigger++;
	}
	return (count);
}

static int	lenght_str(char const *s, char c, int aux)
{
	int	len;
	int	quotes;
	int	prev_quotes;

	len = 0;
	quotes = 0;
	while (quotes == 0 && s[aux] == c && s[aux])
	{
		quotes = split_in_quotes(s[aux], quotes);
		aux++;
	}
	while ((s[aux] != c || quotes != 0) && s[aux])
	{
		prev_quotes = quotes;
		quotes = split_in_quotes(s[aux], quotes);
		if (!is_quote(s[aux]) || is_quote(s[aux]) != quotes)
			len++;
		if (prev_quotes == is_quote(s[aux]) && prev_quotes != 0)
			len--;
		aux++;
	}
	return (len);
}

char	**ft_split_quotes(char const *s, char c)
{
	int		index;
	int		sub_index;
	int		aux;
	char	**split;
	int		quotes;
	int		prev_quotes;

	if (!s)
		return (NULL);
	split = ft_calloc(sizeof(char *), (count_words(s, c) + 1));
	if (!split)
		return (NULL);
	index = -1;
	aux = 0;
	quotes = 0;
	while (++index < count_words(s, c))
	{
		split[index] = malloc((sizeof(char) * lenght_str(s, c, aux)) + 1);
		if (!split[index])
			return (0);
		sub_index = 0;
		while (quotes == 0 && s[aux] == c && s[aux] != '\0')
		{
			quotes = split_in_quotes(s[aux], quotes);
			aux++;
		}
		while ((s[aux] != c || quotes != 0) && s[aux] != '\0')
		{
			prev_quotes = quotes;
			quotes = split_in_quotes(s[aux], quotes);
			if (prev_quotes == is_quote(s[aux]) && prev_quotes != 0)
				aux++;
			if (is_quote(s[aux]) == 0 || is_quote(s[aux]) != quotes)
				split[index][sub_index++] = s[aux];
			aux++;
		}
		split[index][sub_index] = '\0';
	}
	return (split);
}
