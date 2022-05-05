/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:49:06 by ajimenez          #+#    #+#             */
/*   Updated: 2022/05/05 12:40:22 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_iter_raw_x(int *x, int *raw, int n)
{
	while (raw[*x] == n)
		*x += 1;
}

static void	nuclear(int *clean_tokens, int *x, int *aux_clean, int *raw)
{
	if (raw[*x] > -1)
	{
		clean_tokens[*aux_clean] = raw[*x];
		*aux_clean += 1;
		*x += 1;
	}
	if (raw[*x] == -2)
	{
		clean_tokens[*aux_clean] = -1;
		*x += 1;
		ft_iter_raw_x(x, raw, -1);
		clean_tokens[*aux_clean] = -1;
		*aux_clean += 1;
	}
	if (raw[*x] == -3)
	{
		ft_iter_raw_x(x, raw, -3);
		ft_iter_raw_x(x, raw, -1);
	}
	if (raw[*x] == -1)
	{
		clean_tokens[*aux_clean] = -1;
		*aux_clean += 1;
		ft_iter_raw_x(x, raw, -1);
	}
}

int	*clean_tokens(int *raw, int raw_len, int len)
{
	int	*clean_tokens;
	int	x;
	int	aux_clean;

	x = 0;
	aux_clean = 0;
	clean_tokens = ft_calloc(sizeof(int), len);
	if (!clean_tokens)
		return (0);
	while (x < raw_len)
	{
		nuclear(clean_tokens, &x, &aux_clean, raw);
	}
	return (clean_tokens);
}
