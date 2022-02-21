/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:17:19 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/21 15:28:48 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_printlst(t_list *token_lst)
{
	while (token_lst)
	{
		printf("token  %i char * %s\n", ((t_token_data *)token_lst->content)->token, ((t_token_data *)token_lst->content)->str);
		token_lst = token_lst->next;
	}
}

int	*clean_tokens(int *raw, int raw_len, int len)
{
	int	*clean_tokens;
	int	aux_raw;
	int aux_clean;	

	aux_raw = 0;
	aux_clean = 0;	
	clean_tokens = malloc(sizeof(int) * len);
	if (!clean_tokens)
		return (0);
	while (aux_raw < raw_len)
	{
		if (raw[aux_raw] > -1 && aux_clean < len)
		{
			clean_tokens[aux_clean] = raw[aux_raw];
		}
		else
		{
			clean_tokens[aux_clean] = -1;
			printf("%i entra \n", raw[aux_raw]);
			while (raw[aux_raw] == -1 && aux_raw < raw_len)
			{
				aux_raw++;
			}
		}
		//printf("%i ", clean_tokens[aux_clean]);
		aux_clean++;
		aux_raw++;
	}
	printf("\n---\n");
	for (int i = 0; i < raw_len; i++)
			printf("%i ", raw[i]);
	return (clean_tokens);
}

//int	*ft_put_tokens_into_array(char *s)

void lexer(char *s, t_gdata *gdata)
{
	int		aux;
	int		*raw_tokens;
	int 	*clean_tkns;
	int		raw_tokens_len = 0;
	int		clean_len;
	t_list			*token_lst;
	int	n_commands = get_n_commands(s);
	t_token_data	*token_data;

	token_data = ft_calloc(sizeof(t_token_data), 1);
	raw_tokens = ft_calloc(ft_strlen(s) + 1, sizeof(int));
	token_lst = NULL;
	aux = 0;
	gdata->n_commands = get_n_commands(s);
	gdata->n_tokens = get_n_tokens(s);
	handle_input(s, gdata);
	if (gdata->data_error > 0)
		return ; //gestion de comillas abiertas lexer
	//printf("inside %i ", raw_tokens[]);
	int i = 0;
	//printf("ft_strlen %zu\n", ft_strlen(s));
	while (s[aux])
	{
		//raw_tokens[aux] = ft_get_token(s, aux)
		//printf("token = %i", ft_give_token(s[aux], s[aux + 1], &aux));
		if (s[aux + 1])
			raw_tokens[i] = ft_give_token(s[aux], s[aux + 1], &aux);
		else
			raw_tokens[i] = ft_give_token(s[aux], 0, NULL);;
		//printf("char %c int %i \n", s[aux], raw_tokens[aux]);
		//printf("\n");
		i++;
		aux++;
	}
//	for (int i = 0; i < aux; i++)
//		printf(" %i ", raw_tokens[i]);
//	printf("\n-----------------------\n");
	raw_tokens_len = i;
	clean_len = n_commands + gdata->n_tokens;
//	printf("%i n_commands = %i, n_tokens = %i\n", clean_len, n_commands, gdata->n_tokens);
//	printf("\n-----------------------\n");
	clean_tkns = clean_tokens(raw_tokens, aux, clean_len/*n_commands + gdata->n_tokens*/);
	//printf("\n-----------------------\n");
	//for (int i = 0; i < clean_len; i++)
	//		printf("%i ", clean_tkns[i]);
	//for (int i = 0; i < clean_len; i++)
	//		printf("%i ", clean_tkns[i]);
	//printf("\n-----------------------\n");
	ft_insert_data_lst(&token_lst, token_data, clean_tkns, clean_len/*n_commands + gdata->n_tokens*/);
	ft_convert_matrix(gdata->cmds, token_lst);
	clean_lst_tokens(token_lst);
	ft_printlst(token_lst);
}
