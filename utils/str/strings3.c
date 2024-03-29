/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:25:28 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/22 13:58:15 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cpy_str_no_quotes(char *cmd)
{
	int		l;
	int		i;
	int		quote_type;
	char	*word;

	i = -1;
	l = 0;
	quote_type = 0;
	word = ft_calloc(sizeof(char *), (length_str_no_quotes(cmd) + 1));
	if (!word)
		return (0);
	while (cmd[++i])
	{
		if (quote_type == is_quote(cmd[i]))
			quote_type = 0;
		if (!quote_type && is_quote(cmd[i]))
			quote_type = is_quote(cmd[i]);
		if (is_quote(cmd[i]) != quote_type)
			word[l++] = cmd[i];
		else if (!is_quote(cmd[i]))
			word[l++] = cmd[i];
	}
	word[l] = '\0';
	free(cmd);
	return (word);
}

static int	size_to_space(char *cmd)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (is_quote(cmd[i]))
		i++;
	while (cmd[i] && (cmd[i] != ' ' || !is_quote(cmd[i])))
	{
		i++;
		l++;
	}
	return (l);
}

char	*cpy_until_space(char *cmd)
{
	int		i;
	int		l;
	char	*word;

	word = malloc(sizeof(char *) + (size_to_space(cmd) + 1));
	if (!word)
		return (0);
	i = 0;
	l = 0;
	while (is_quote(cmd[i]))
		i++;
	while (cmd[i] && !is_quote(cmd[i]) && cmd[i] != ' ')
	{
		word[l] = cmd[i];
		i++;
		l++;
	}
	word[i] = '\0';
	return (word);
}

char	*append_nl(char *str)
{
	int		i;
	char	*word;

	if (!str)
		return (0);
	word = malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!word)
		return (0);
	i = -1;
	while (str[++i])
		word[i] = str[i];
	word[i] = '\n';
	word[i + 1] = '\0';
	free(str);
	return (word);
}
