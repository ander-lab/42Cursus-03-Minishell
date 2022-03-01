/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:18:10 by ajimenez          #+#    #+#             */
/*   Updated: 2022/03/01 12:17:26 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_printlst(t_list *token_lst)
{
	while (token_lst)
	{
		//printf("----hell");
		printf("token  %i char * %s\n", ((t_token_data *)token_lst->content)->token,
			((t_token_data *)token_lst->content)->str);
		//token_data = token_lst->content;
		//printf(" token 2= %i\n", token_data->token);
		token_lst = token_lst->next;
	}
}

//int	*ft_put_tokens_into_array(char *s)

//int ft_count_spec_tokens(int *arr, int len)
//{
//	int	count;
//	int	aux;
//	
//	count = 0; aux = 0;
//	while (aux < len)
		//	{
//		if (arr[aux] == 3 || arr[aux] == 4)
//			count++;
//		aux++;
//	}
//	return (count);
//}

int	put_tokens_on_arr(char *s, int *raw_tokens)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (s[i])
	{
		raw_tokens[l] = ft_get_token(s, &i);
		i++;
		l++;
	}
	return (l);
}


void lexer(char *s, t_gdata *gdata)
{
	int		*raw_tokens;
	int		raw_len;
	int 	*clean_tkns;
	int		clean_len;
	t_list			*token_lst;
	t_token_data	*token_data;

	token_data = ft_calloc(sizeof(t_token_data), 1);
	raw_tokens = ft_calloc(ft_strlen(s) + 2, sizeof(int));
	token_lst = NULL;
	gdata->n_commands = get_n_commands(s);
	gdata->n_tokens = get_n_tokens(s);
	int	n_commands = get_n_commands(s);
	handle_input(s, gdata);
	if (gdata->data_error > 0)
		return ; //gestion de comillas abiertas lexer
	raw_len = put_tokens_on_arr(s, raw_tokens);
	clean_len = n_commands + gdata->n_tokens;
	printf("CLEAN_LEN: %d\n", clean_len);
	clean_tkns = clean_tokens(raw_tokens, raw_len, clean_len, n_commands, s);
	ft_insert_data_lst(&token_lst, token_data, clean_tkns, clean_len);
	ft_printlst(token_lst);
	printf("\n-----------------------\n");
	ft_convert_matrix(gdata->cmds, token_lst);
	clean_lst_tokens(token_lst);
	ft_printlst(token_lst);
}
