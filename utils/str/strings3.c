/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:25:28 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/31 10:29:09 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cpy_str_no_quotes(char *cmd)
{
	int		l;
	int		i;
	int		quote_type;
	char	*word;

	i = 0;
	l = 0;
	quote_type = 0;
	word = ft_calloc(sizeof(char *), (length_str_no_quotes(cmd) + 1));
	if (!word)
		return (0);
	while (cmd[i])
	{
		if (quote_type == is_quote(cmd[i]))
			quote_type = 0;
		if (!quote_type && is_quote(cmd[i]))
			quote_type = is_quote(cmd[i]);
		if (is_quote(cmd[i]) != quote_type)
			word[l++] = cmd[i];
		else if (!is_quote(cmd[i]))
			word[l++] = cmd[i];
		i++;
	}
	word[l] = '\0';
	free(cmd);
	return (word);
}

char	*cpy_until_space(char *cmd)
{
	int		i;
	int		l;
	char	*word;

	i = 0;
	l = 0;
	while (is_quote(cmd[i]))
		i++;
	while (cmd[i])
	{
		if (cmd[i] == ' ' || is_quote(cmd[i]))
			break ;
		i++;
		l++;
	}
	word = malloc(sizeof(char *) + (l + 1));
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
	int	i;
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
