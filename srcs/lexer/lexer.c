/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:17:19 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/22 10:54:06 by ajimenez         ###   ########.fr       */
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

int	*clean_tokens(int *raw, int raw_len, int len)
{
	int	*clean_tokens;
	int	aux_raw = 0;
	int aux_clean = 0;	

	clean_tokens = malloc(sizeof(int) * len);
	if (!clean_tokens)
		return (0);
	while (aux_raw < raw_len)
	{
		if (raw[aux_raw] > -1 && aux_clean < len)
			clean_tokens[aux_clean] = raw[aux_raw];
		else
		{
			clean_tokens[aux_clean] = -1;
			while (raw[aux_raw + 1] == -1 && aux_raw < raw_len && aux_clean < len)
			{
				aux_raw++;
			}
		}
		aux_clean++;
		aux_raw++;
	}
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
	if (gdata->data_error > 0)
		return ; //gestion de comillas abiertas lexer
	//printf("\n-----------------------\n");
	int i = 0;
	while (s[aux])
	{
		if (s[aux + 1])
			raw_tokens[i] = ft_give_token(s[aux], s[aux + 1], &aux);
		else
			raw_tokens[i] = ft_give_token(s[aux], 0, NULL);
		i++;
		aux++;
	}
	raw_tokens_len = aux;
	clean_len = n_commands + gdata->n_tokens;
	clean_tkns = clean_tokens(raw_tokens, aux, clean_len);
	ft_insert_data_lst(&token_lst, token_data, clean_tkns, clean_len);
	ft_convert_matrix(gdata->cmds, token_lst);
	clean_lst_tokens(token_lst);
	ft_printlst(token_lst);
}
