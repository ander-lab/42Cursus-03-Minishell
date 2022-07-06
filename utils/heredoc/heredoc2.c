/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:21:09 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/06 12:15:01 by goliano-         ###   ########.fr       */
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
			break;
	}
	return (lst);
}

t_dlist	*iterate_red_app(t_dlist *lst)
{
	int prev;

	prev = get_prev_type(lst);
	while (prev == 2 || prev == 4)
	{
		lst = lst->prev;
		if (!lst->prev)
			break ;
		lst = lst->prev;
		prev = get_prev_type(lst);
	}
	return (lst);
}

t_dlist	*iterate_ind(t_dlist *lst)
{
	int	tkn;

	if (!lst)
		return (lst);
	printf("HOLA\n");
	tkn = ((t_token_data *)lst->content)->token;
	printf("TKN22: %d\n", tkn);
	while (tkn == 1)
	{
		lst = lst->next;
		if (lst->next)
			lst = lst->next;
		tkn = ((t_token_data *)lst->content)->token;
	}
	return (lst);
}
