/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:49:06 by ajimenez          #+#    #+#             */
/*   Updated: 2022/05/06 11:55:17 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_iter_raw_x(int *x, int *raw, int n)
{
	while (raw[*x] == n)
		*x += 1;
}

void	raw_three(int *x, int *raw)
{
	while (raw[*x] == -3)
		*x += 1;
	while (raw[*x] == -1)
		*x += 1;
}

void	raw_two(int *x, int *raw, int *aux_clean, int *clean_tokens)
{
	clean_tokens[*aux_clean] = -1;
	*aux_clean += 1;
	*x += 1;
	while (raw[*x] == -1)
		*x += 1;
	clean_tokens[*aux_clean] = -1;
	*aux_clean += 1;
}

void	raw_one(int *x, int *raw, int *aux_clean, int *clean_tokens)
{
	clean_tokens[*aux_clean] = raw[*x];
	*aux_clean += 1;
	*x += 1;
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
		if (raw[x] > -1)
			raw_one(&x, raw, &aux_clean, clean_tokens);
		if (raw[x] == -2)
			raw_two(&x, raw, &aux_clean, clean_tokens);
		if (raw[x] == -3)
			raw_three(&x, raw);
		if (raw[x] == -1)
		{
			clean_tokens[aux_clean] = -1;
			aux_clean++;
			ft_iter_raw_x(&x, raw, -1);
		}
	}
	return (clean_tokens);
}
