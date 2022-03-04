/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:21:18 by goliano-          #+#    #+#             */
/*   Updated: 2022/03/04 12:09:28 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	spaces_or_null(char *s)
{
	int	exists;
	int	i;

	exists = 1;
	i = 0;
	while (s[i] && exists == 1)
	{
		if (s[i] != ' ')
			exists = 0;
		i++;
	}
	return (exists);
}

char	*remove_ind_red(char *s)
{
	char	*aux;
	int		i;
	int		quotes;
	int		x;

	i = -1;
	x = -1;
	aux = ft_calloc(sizeof(char), (ft_strlen(s) + 1));
	if (!aux)
		return (s);
	quotes = 0;
	while (s[++i])
	{
		if (is_quote(s[i]) == 1)
			quotes = is_in_quotes(quotes, 1);
		if (is_quote(s[i]) == 2)
			quotes = is_in_quotes(quotes, 2);
		if (quotes == 0 && s[i] != '<' && s[i] != '>')
			aux[++x] = s[i];
		if (quotes == 1 || quotes == 2)
			aux[++x] = s[i];
	}
	free(s);
	return (aux);
}

int	exists_word(char *s)
{
	int	exists;
	int	i;

	exists = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			exists = 1;
		i++;
	}
	return (exists);
}

int	is_cmd_between_tokens(char *s, int idx)
{
	int	token;
	int	cmd_exists;

	token = 0;
	cmd_exists = 0;
	while (s[++idx])
	{
		token = ft_get_token(s, &idx);
		if (token != -1)
			return (cmd_exists);
		if (token == -1 && s[idx] != ' ')
			cmd_exists = 1;
	}
	return (cmd_exists);
}

char	*get_until_token(int prev_l, int l, char *str)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (l - prev_l + 1));
	if (!word)
		return (0);
	i = 0;
	while (prev_l < l)
	{
		word[i] = str[prev_l];
		i++;
		prev_l++;
	}
	word[i] = '\0';
	word = remove_ind_red(word);
	return (word);
}
