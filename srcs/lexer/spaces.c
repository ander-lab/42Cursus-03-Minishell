/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:46:51 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/05 10:57:04 by ajimenez         ###   ########.fr       */
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
