/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:36:17 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/09 15:07:53 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int	ft_give_token(char c1, char c2, int *aux)
{
	if (c1 == '|')
		return (PIPE);
	else if (c1 == '<')
	{
		if (c2 == '<')
		{
			*aux = *aux + 1;
			return (HERE_DOC);
		}
		else
			return (INDIRECTION);
	}	
	else if (c1 == '>')
	{
		if (c2 == '>')
		{
			*aux = *aux + 1;
			return (APPEND);
		}
		else
			return (REDIRECTION);
	}	
	return (-1);
}

void lexer(char *s)
{
	int		aux;
	int		i = 0;
	//t_list			**token_lst;
	//t_token_data	*token_data;

	//token_data = ft_calloc(sizeof(t_token_data), 1);
	aux = 0;
	//token_lst = 0;
	//token_data = 0;
	//token_data->token = 0;
	while (s[aux])
	{
		if (s[aux + 1])
			i = ft_give_token(s[aux], s[aux + 1], &aux);
		else
			i = ft_give_token(s[aux], 0, NULL);
		//ft_lstadd_back(token_lst, ft_lstnew(token_data));
		printf("aux = %i char = %c = %i\n", aux, s[aux], i);
		aux++;
	}
}
