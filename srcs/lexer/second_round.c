/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_round.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:50:54 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/16 13:52:29 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define NEXT 1

int	ft_checkpipe(int token, int next_token)
{
	if (token == PIPE && next_token == ARGUMENT)
		return (NEXT);
	return (0);
}

void	ft_changevalue(t_list **lst, int val, int pos)
{
	if (pos == NEXT || val == FILE_NAME)
	{
		if (((t_token_data *)(*lst)->next->content)->token == -1)
			((t_token_data *)(*lst)->next->content)->token = val;
	}
	else if (val == ARGUMENT)
		if (((t_token_data *)(*lst)->content)->token == -1)
			((t_token_data *)(*lst)->content)->token = val;
}

int	ft_tokenizer(int token, int next_token)
{
	if (next_token != FILE_NAME && next_token != ARGUMENT && next_token != -1)
	{
		if (token == -1)
			token = ARGUMENT;
	}
	else if (next_token == -1)
	{
		if (token == PIPE)
			token = ARGUMENT;
		else if (token == INDIRECTION || token == REDIRECTION
			|| token == HERE_DOC || token == APPEND)
			token = FILE_NAME;
	}
	return (token);
}

void	lexer_lst(t_list *token_lst)
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
		ft_changevalue(&token_lst, new_token, ft_checkpipe(token, new_token));
		token_lst = token_lst->next;
	}
}