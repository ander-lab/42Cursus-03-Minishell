/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:50:28 by ajimenez          #+#    #+#             */
/*   Updated: 2022/03/02 16:54:49 by ajimenez         ###   ########.fr       */
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

int	*clean_tokens(int *raw, int raw_len, int len)
{
	int	*clean_tokens;
	int	x = 0;
	int aux_clean = 0;
	int	prev_token;

	clean_tokens = ft_calloc(sizeof(int), len);
	if (!clean_tokens)
		return (0);
	while (x < raw_len)
	{
		if (raw[x] > -1)
		{
			prev_token = raw[x];
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
