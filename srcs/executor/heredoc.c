/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:32:42 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/31 15:17:53 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	heredoc_count(t_dlist *lst)
{
	int	c;
	int	tkn;
	int	next;

	c = 0;
	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
		{
			lst = lst->next;
			next = get_next_type(lst);
			if (next == 0 || next == -1)
				c++;
		}
		lst = lst->next;
	}
	return (c);
}

static int	store_heredoc(t_dlist *lst)
{
	int	store;
	int	next;

	store = 0;
	next = get_next_type(lst);
	if (next == 0 || next == -1)
		store = 1;
	return (store);
}

void	do_heredoc(t_dlist *lst, t_gdata *gdata)
{
	char	*cmd;
	int		store;
	char	*here;
	int		x;

	gdata->heredoc = ft_calloc(sizeof(char *), heredoc_count(lst) + 1);
	x = -1;
	while (exists_heredoc(lst))
	{
		lst = go_heredoc(lst);
		cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
		if (has_quotes(cmd))
			cmd = cpy_str_no_quotes(cmd);
		store = store_heredoc(lst);
		here = fill_heredoc(cmd);
		if (store)
			gdata->heredoc[++x] = here;
		else
			free(here);
		free(cmd);
	}
}
