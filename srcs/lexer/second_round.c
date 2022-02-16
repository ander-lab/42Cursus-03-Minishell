/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_round.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:50:54 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/16 13:24:06 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define NEXT 1
//#define SAME 1

int ft_checkpipe(int token, int next_token)
{
	if (token == PIPE && next_token == ARGUMENT)
		return (NEXT);
	return (0);
}

void	ft_changevalue(t_list **lst, int val, int pos)
{
	if (pos == NEXT || val == FILE_NAME)
	{
	 	((t_token_data *)(*lst)->next->content)->token = val;
	}
	else if (val == ARGUMENT)
		((t_token_data *)(*lst)->content)->token = val;
}

int	ft_is_filename(int token, int next_token)
{
	if (token == INDIRECTION || token == REDIRECTION
		|| token == HERE_DOC || token == APPEND)
	{
		if (next_token == -1)
			return (FILE_NAME);
	}
	return (0);
}

int	ft_is_cmd(int token, int next_token)
{
	if (next_token == INDIRECTION || next_token == REDIRECTION
	|| next_token == HERE_DOC || next_token == APPEND || next_token == PIPE)
	{
		if (token == -1)
			return (ARGUMENT);
	}
	else if (next_token == -1)
	{
		if (token == PIPE)
			return (ARGUMENT);
	}
	return (0);
}

int	ft_tokenizer(int token, int next_token)
{
	if (ft_is_filename(token, next_token))
			token = FILE_NAME;
	else if (ft_is_cmd(token, next_token))
			token = ARGUMENT;
	return (token);
}


void lexer_lst(t_list *token_lst)
{
	int	token;
	int	token_next;
	int	new_token;

	token = ((t_token_data *)token_lst->content)->token;
	if (ft_lstsize(token_lst) == 1 && token == -1)
		ft_changevalue(&token_lst, ARGUMENT, 0);
	while (token_lst->next)
	{
		token = ((t_token_data *)token_lst->content)->token;
		token_next = ((t_token_data *)token_lst->next->content)->token;
		new_token = ft_tokenizer(token, token_next);
		printf("%i", ft_checkpipe(token, new_token));
		ft_changevalue(&token_lst, new_token, ft_checkpipe(token, new_token));
		token_lst = token_lst->next;
	}
}

