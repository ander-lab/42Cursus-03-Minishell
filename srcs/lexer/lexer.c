/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:36:17 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/15 11:26:47 by ajimenez         ###   ########.fr       */
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

t_list	*ft_lstnew_struct(void *newcontent, size_t size)
{
	t_list	*new;
	void	*content;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	content = malloc(size);
	if (!content)
	{
		free(new);
		return (NULL);
	}
	ft_memcpy(content, newcontent, size);
	new->content = content;
	new->next = NULL;
	return (new);
}

void lexer(char *s, t_gdata *gdata)
{
	int		aux;
	t_list			*token_lst;
	t_token_data	*token_data;

	token_data = ft_calloc(sizeof(t_token_data), 1);
	token_lst = ft_lstnew(token_data);
	aux = 0;
	gdata->n_commands = get_n_commands(s);
	handle_input(s, gdata);
	//token_lst = 0;
	//token_data = 0;
	//token_data->token = 0;
	while (s[aux])
	{
		if (s[aux + 1])
			token_data->token = ft_give_token(s[aux], s[aux + 1], &aux);
		else
			token_data->token = ft_give_token(s[aux], 0, NULL);
		ft_lstadd_back(&token_lst, ft_lstnew_struct(token_data, sizeof(t_token_data)));
	//	printf("aux = %i char = %c = %i\n", aux, s[aux], token_data->token);
		aux++;
	}
	while (token_lst->next)
	{
		//printf("%i\n", ((t_token_data *)token_lst->content)->token);
		token_data = token_lst->content;
	//	printf(" token = %i\n", token_data->token);
		token_lst = token_lst->next;
	}
}
