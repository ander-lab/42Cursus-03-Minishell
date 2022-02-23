/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:50:28 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/23 15:25:54 by ajimenez         ###   ########.fr       */
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

int	*clean_tokens(int *raw, int raw_len, int len, int n_commands, char *s)
{
	int	*clean_tokens;
	int	aux_raw = 0;
	int aux_clean = 0;	

//	printf("n_commands %i\n", n_commands);
	//raw_len -= ft_len_without_ceros(raw, raw_len, s);
//	printf("\n---------CLEAN-----------\n");
//	for (int x = 0; x < raw_len; x++)
//		printf("%i ", raw[x]);
	s += 0;
	clean_tokens = ft_calloc(sizeof(int), len);
	if (!clean_tokens)
		return (0);
	while (aux_raw < raw_len)
	{
		if (raw[aux_raw] > -1 && aux_clean < len && aux_raw < raw_len)
		{
		//	printf("%i \n", raw[aux_raw]);
			clean_tokens[aux_clean] = raw[aux_raw];
		}
		else if (n_commands)
		{
			n_commands--;
			//if (raw[aux_raw + 1] == -1 && raw[aux_raw + 1] == -1)
			//{
		//		printf("entra %i\n", raw[aux_raw]);
				clean_tokens[aux_clean] = -1;
		//		aux_raw++;
			//}
			while (raw[aux_raw + 1] == -1 && aux_raw < raw_len && aux_clean < len)
			{
				aux_raw++;
			}
		//	printf("n_commands %i\n", n_commands);
		}
		aux_clean++;
		aux_raw++;
		//printf("clean_tokens ");
		//for (int x = 0; x < aux_clean; x++)
		//	printf("%i ", clean_tokens[x]);
		//printf("\n");
	}
	return (clean_tokens);
}
