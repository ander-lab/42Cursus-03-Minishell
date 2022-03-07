/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:50:28 by ajimenez          #+#    #+#             */
/*   Updated: 2022/03/07 10:25:39 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//int ft_count_spaces()

//int ft_len_without_ceros(int *raw, int len, char *s)
//{
//	int	before_zero = len;
//	int	aux = len;
//	printf("len %i \n", aux);
//	while(raw[aux] == 0)
//		aux--;
//	//count pipes
//	while (s[before_zero] == '|')
//	{
//		aux++;
//		before_zero--;
//	}
////	if (before_zero != len)
////		aux = aux - before_zero;
//	printf("ceros %i \n", aux);
//	return (aux);
//}

int	is_file_token(int t)
{
	int	it_is;

	it_is = 0;
	if (t > 0 && t < 5)
		it_is = 1;
	return (it_is);
}

static int *ft_duparr(const int *arr, int len)
{
	int	*arr_dup;

	arr_dup = (int *)malloc(len + 1 * sizeof(int));
	if (!arr_dup)
		return (0);
	ft_memcpy(arr_dup, arr, len + 1);
	return (arr_dup);
}

int *spaces(char *s, int *raw, int raw_len)
{
	int	*spaces;
	int	aux_raw;
	int	aux_str;

	aux_raw = 0;
	aux_str = 0;
	spaces = ft_duparr(raw, raw_len);
	while (raw[aux_raw] < raw_len)
	{
		if (raw[aux_raw] == 4 || raw[aux_raw] == 3)
			aux_str++;
		if (s[aux_str] == ' ' && raw[aux_raw] == -1)
			spaces[aux_raw] = -3;
		aux_raw++;
	}
	return (spaces);
}

int	*clean_tokens(int *raw, int raw_len, int len)
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
			x++;
		}
		else if (raw[x] == -2)
		{
			clean_tokens[aux_clean] = -1;
			aux_clean++;
			x++;
			while (raw[x] == -1)
				x++;
			clean_tokens[aux_clean] = -1;
		}
		else if (raw[x] == -3)
		{
			//clean_tokens[aux_clean] = -3;
			while (raw[x] == -3)
				x++;
			while (raw[x] == -1)
				x++;
		}
		else if (raw[x] == -1)
		{
			clean_tokens[aux_clean] = -1;
			while (raw[x] == -1)
				x++;
		}
		aux_clean++;
	}
	return (clean_tokens);
}
