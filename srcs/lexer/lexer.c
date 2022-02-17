/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:17:19 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/17 16:10:54 by goliano-         ###   ########.fr       */
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

int	*clean_tokens(int *raw, int raw_len, int len)
{
	int	*clean_tokens;
	int	aux = 0;
	int aux_clean = 0;	

	printf("raw len : %d len: %d\n", raw_len, len);
	clean_tokens = ft_calloc(sizeof(int), len);
	if (!clean_tokens)
		return (0);
	while (aux < raw_len)
	{
		if (raw[aux] > -1)
			clean_tokens[aux_clean] = raw[aux];
		else
		{
			clean_tokens[aux_clean] = -1;
			while (raw[aux + 1] == -1 && aux < raw_len)
			{
				//printf("%d ", aux);
				aux++;
			}
		}
	//	printf("%d", raw[1]);
	//	printf("%d", raw[2]);
	//	printf("%d", raw[3]);
		printf("%d", aux_clean);
		aux_clean++;
		aux++;
		//printf("clean %d raw   %d\n", clean_tokens[aux_clean], raw[aux]);
	}
	printf("\n %d ----------------------------------\n", len);
	for (int i = 0; i < len; i++)
		printf("%d ", clean_tokens[i]);
	printf("\n----------------------------------\n");
	return (0);
}

void lexer(char *s, t_gdata *gdata)
{
	int		aux;
	int		*raw_tokens;
	//int		raw_tokens_len = 0;;
	t_list			*token_lst;
	t_token_data	*token_data;

	token_data = ft_calloc(sizeof(t_token_data), 1);
	raw_tokens = ft_calloc(ft_strlen(s), sizeof(int));
	token_lst = NULL;
	aux = 0;
	gdata->n_commands = get_n_commands(s);
	printf("N_COMMANDS: %d\n", gdata->n_commands);
	gdata->n_tokens = get_n_tokens(s);
	//int	n_commands = get_n_commands(s);
	//printf("N_commands: %d N_tk: %d\n", gdata->n_commands, gdata->n_tokens);
	//handle_input(s, gdata);
	//printf("\n-----------------------\n");
	/*while (s[aux])
	{
		if (s[aux + 1])
			raw_tokens[aux] = ft_give_token(s[aux], s[aux + 1], &aux);
		else
			raw_tokens[aux] = ft_give_token(s[aux], 0, NULL);
		//ft_lstadd_back(&token_lst, ft_lstnew_struct(token_data, sizeof(t_token_data)));
		aux++;
	}
//	for (int i = 0; i < aux; i++)
//		printf("%d ", raw_tokens[i]);
//	printf("\n----------------------------------\n");
	//raw_tokens_len = aux;
	clean_tokens(raw_tokens, aux, n_commands + gdata->n_tokens);*/
	//ft_printlst(token_lst);
	//lexer_lst(token_lst);
	//printf("\n-----------------------\n");
	//ft_printlst(token_lst);
}
