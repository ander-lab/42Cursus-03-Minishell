/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:21:09 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/18 14:45:43 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dlist	*go_heredoc(t_dlist *lst)
{
	int	tkn;

	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		lst = lst->next;
		if (tkn == 3)
			break ;
	}
	return (lst);
}

t_dlist	*iterate_red_app(t_dlist *lst)
{
	int	tkn;

	tkn = ((t_token_data *)lst->content)->token;
	while (tkn == 2 || tkn == 4)
	{
		lst = lst->next;
		if (lst->next)
			lst = lst->next;
		tkn = ((t_token_data *)lst->content)->token;
	}
	lst = lst->prev;
	return (lst);
}

t_dlist	*iterate_ind(t_dlist *lst)
{
	int	tkn;

	if (!lst)
		return (lst);
	tkn = ((t_token_data *)lst->content)->token;
	while (tkn == 1)
	{
		lst = lst->next;
		if (lst->next)
			lst = lst->next;
		tkn = ((t_token_data *)lst->content)->token;
	}
	return (lst);
}
