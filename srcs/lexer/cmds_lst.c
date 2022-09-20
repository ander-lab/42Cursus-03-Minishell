/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:48:03 by goliano-          #+#    #+#             */
/*   Updated: 2022/09/12 14:15:48 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dlist	*iter_to_pipe(t_dlist *lst)
{
	int	tkn;

	while (lst)
	{
		tkn = (((t_token_data *)lst->content)->token);
		if (tkn == 0)
		{
			lst = lst->next;
			break ;
		}
		lst = lst->next;
	}
	return (lst);
}

t_dlist	*move_to_last_heredoc(t_dlist *lst)
{
	int		tkn;
	t_dlist	*aux;

	aux = lst;
	tkn = (((t_token_data *)lst->content)->token);
	while (lst && tkn != 0)
	{
		if (tkn == 3)
			aux = lst->next;
		lst = lst->next;
		if (lst)
			tkn = (((t_token_data *)lst->content)->token);
	}
	return (aux);
}

int	exists_heredoc_until_pipe(t_dlist *lst)
{
	int	tkn;
	int	exist;

	tkn = (((t_token_data *)lst->content)->token);
	exist = 0;
	while (lst && tkn != 0)
	{
		if (tkn == 3)
			exist = 1;
		lst = lst->next;
		if (lst)
			tkn = (((t_token_data *)lst->content)->token);
	}
	return (exist);
}

int	need_exec_here(t_dlist *lst)
{
	int	tkn;
	int	need_it;

	need_it = 0;
	tkn = 0;
	if (exists_heredoc_until_pipe(lst))
	{
		lst = move_to_last_heredoc(lst);
		lst = lst->next;
		if (!lst)
			return (1);
		tkn = (((t_token_data *)lst->content)->token);
		if (tkn == 0)
			return (1);
	}
	return (need_it);
}
