/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:17:19 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/23 15:25:01 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_printlst(t_list *token_lst)
{
	while (token_lst)
	{
		//printf("----hell");
		printf("token  %i char * %s\n", ((t_token_data *)token_lst->content)->token, ((t_token_data *)token_lst->content)->str);
		//token_data = token_lst->content;
		//printf(" token 2= %i\n", token_data->token);
		token_lst = token_lst->next;
	}
}

//int	*ft_put_tokens_into_array(char *s)

int ft_count_spec_tokens(int *arr, int len)
{
	int	count;
	int	aux;
	
	count = 0;
	aux = 0;
	while (aux < len)
	{
		if (arr[aux] == 3 || arr[aux] == 4)
			count++;
		aux++;
	}
	return (count);
}

void lexer(char *s, t_gdata *gdata)
{
	int		aux;
	int		*raw_tokens;
	int 	*clean_tkns;
	int		raw_tokens_len = 0;
	int		clean_len;
	t_list			*token_lst;
	t_token_data	*token_data;

	token_data = ft_calloc(sizeof(t_token_data), 1);
	raw_tokens = ft_calloc(ft_strlen(s) + 2, sizeof(int));
	token_lst = NULL;
	aux = 0;
	gdata->n_commands = get_n_commands(s);
	printf("N_COMMADS: %d\n", gdata->n_commands);
	gdata->n_tokens = get_n_tokens(s);
	int	n_commands = get_n_commands(s);
	handle_input(s, gdata);
	//int i = 0;
	//while (gdata->cmds[i])
	//{
	//	printf("DATA: %s\n", gdata->cmds[i]);
	//	i++;
	//}
	//TODO -> Contar appends y here docs para reservar memoria antes del raw_tokens;
	if (gdata->data_error > 0)
		return ; //gestion de comillas abiertas lexer
	int i = 0;
	while (s[aux])
	{
		if (s[aux + 1])
			raw_tokens[i] = ft_give_token(s[aux], s[aux + 1], &aux);
		else
			raw_tokens[i] = ft_give_token(s[aux], 0, NULL);
	//	if (raw_tokens[i] == 4 || raw_tokens[i] == 3)
	//		aux--;
		i++;
		aux++;
	}
	raw_tokens = ft_recalloc(raw_tokens, ft_count_spec_tokens(raw_tokens, aux));
	//raw_tokens[aux] -= (count_chars(3, (char *)raw_tokens) + count_chars(4, (char *)raw_tokens));
	printf("\n-----------------------\n");
	raw_tokens_len = aux;
	clean_len = n_commands + gdata->n_tokens;
	clean_tkns = clean_tokens(raw_tokens, aux, clean_len, n_commands, s);
	for (int x = 0; x < clean_len; x++)
		printf("%i ", clean_tkns[x]);
	printf("\n-----------------------\n");
	ft_insert_data_lst(&token_lst, token_data, clean_tkns, clean_len);
	ft_convert_matrix(gdata->cmds, token_lst);
	clean_lst_tokens(token_lst);
	ft_printlst(token_lst);
}
