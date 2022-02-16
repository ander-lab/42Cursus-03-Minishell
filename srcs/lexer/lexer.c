/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:17:19 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/16 15:21:25 by ajimenez         ###   ########.fr       */
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
	}	else if (c1 == '>')
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

void ft_printlst(t_list *token_lst)
{
	while (token_lst)
	{
		//printf("----hell");
		printf("token  %i \n", ((t_token_data *)token_lst->content)->token);
		//token_data = token_lst->content;
		//printf(" token 2= %i\n", token_data->token);
		token_lst = token_lst->next;
	}
}

void lexer(char *s, t_gdata *gdata)
{
	int		aux;
	t_list			*token_lst;
	t_token_data	*token_data;

	token_data = ft_calloc(sizeof(t_token_data), 1);
	token_lst = NULL;
	aux = 0;
	gdata->n_commands = get_n_commands(s);
	handle_input(s, gdata);
	printf("\n-----------------------\n");
	while (s[aux])
	{
		if (s[aux + 1])
			token_data->token = ft_give_token(s[aux], s[aux + 1], &aux);
		else
			token_data->token = ft_give_token(s[aux], 0, NULL);
		ft_lstadd_back(&token_lst, ft_lstnew_struct(token_data, sizeof(t_token_data)));
		aux++;
	}
	//ft_printlst(token_lst);
	lexer_lst(token_lst);
	printf("\n-----------------------\n");
	//ft_printlst(token_lst);
}
