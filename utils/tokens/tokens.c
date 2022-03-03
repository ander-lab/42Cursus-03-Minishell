/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:29:59 by goliano-          #+#    #+#             */
/*   Updated: 2022/03/03 15:34:29 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_n_tokens(char *s)
{
	int	i;
	int	nt;
	int	token;

	i = 0;
	nt = 0;
	token = 0;
	while (s[i])
	{
		token = ft_get_token(s, &i);
		if (token >= PIPE)
			nt++;
		i++;
	}
	return (nt);
}

int	ft_give_token(char c1, char c2, int *aux)
{
	if (c1 == '|')
		return (PIPE);
	else if (c1 == '<')
	{
		if (c2 == '<')
		{
			*aux = *aux + 1;
			return (HERE_DOC);
		}
		else
			return (INDIRECTION);
	}
	else if (c1 == '>')
	{
		if (c2 == '>')
		{
			*aux = *aux + 1;
			return (APPEND);
		}
		else
			return (REDIRECTION);
	}	
	return (-1);
}

int	ft_get_token(char *s, int *l)
{
	int	token;

	token = 0;
	if (s[*l + 1])
		token = ft_give_token(s[*l], s[*l + 1], l);
	else
		token = ft_give_token(s[*l], 0, NULL);
	return (token);
}

int	ends_with_token(char *s)
{
	int	ends;
	int	l;

	l = ft_strlen(s);
	ends = 0;
	if (l == 0)
		return (ends);
	if (s[l - 1] == '>' || s[l - 1] == '<' || s[l - 1] == '|')
		ends = 1;
	return (ends);
}

int	starts_with_token(char *s)
{
	int	starts;
	int	token;
	int	i;

	i = 0;
	starts = 0;
	while (s[i])
	{
		token = ft_get_token(s, &i);
		if ((i == 0 || i == 1) && token > -1)
			starts = 1;
		i++;
	}
	return (starts);
}
