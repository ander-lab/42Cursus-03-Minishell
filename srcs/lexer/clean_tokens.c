/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:49:06 by ajimenez          #+#    #+#             */
/*   Updated: 2022/05/09 13:36:35 by goliano-         ###   ########.fr       */
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
	printf("LEN: %d\n", len);
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
			//printf("clean: %d\n", clean_tokens[aux_clean]);
			aux_clean++;
			ft_iter_raw_x(&x, raw, -1);
		}
	}
	return (clean_tokens);
}

/*int	*clean_tokens(int *raw, int raw_len, int len)
{
	int	*clean_tokens;
	int	x = 0;
	int aux_clean = 0;

	clean_tokens = ft_calloc(sizeof(int), len);
	if (!clean_tokens)
		return (0);
	while (x < raw_len)
	{
		if (raw[x] > -1)
		{
			clean_tokens[aux_clean] = raw[x];
			aux_clean++;
			x++;
		}
		if (raw[x] == -2)
		{
			clean_tokens[aux_clean] = -1;
			aux_clean++;
			x++;
			while (raw[x] == -1)
				x++;
			clean_tokens[aux_clean] = -1;
			aux_clean++;
		}
		if (raw[x] == -3)
		{
			//clean_tokens[aux_clean] = -3;
			while (raw[x] == -3)
				x++;
			while (raw[x] == -1)
				x++;
		}
		if (raw[x] == -1)
		{
			clean_tokens[aux_clean] = -1;
			aux_clean++;
			while (raw[x] == -1)
				x++;
		}
	}
	int h = 0;
	printf("LEN0: %d\n", raw_len);
	printf("LEN1: %d\n", aux_clean);
	printf("LEN2: %d\n", len);
	while (h < aux_clean)
	{
		printf("CLEAN[h]: %d %d \n", h, clean_tokens[h]);
		h++;
	}
	return (clean_tokens);
}*/
