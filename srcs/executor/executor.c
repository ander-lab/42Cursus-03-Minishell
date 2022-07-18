/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:17:54 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/18 15:58:58 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	exists_pipe(t_dlist *lst)
{
	int	exists;
	int	tkn;

	exists = 0;
	while (lst && !exists)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 0)
			exists = 1;
		lst = lst->next;
	}
	return (exists);
}

static int	get_n_pipes(t_dlist *lst)
{
	int	tkn;
	int	pipes;

	pipes = 0;
	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 0)
			pipes++;
		lst = lst->next;
	}
	return (pipes);
}

void	executor(t_gdata *gdata)
{
	t_dlist	*lst;
	t_cmds	*cmds;

	cmds = gdata->cmds_lst;
	lst = gdata->glob_lst;
	gdata->n_pipes = get_n_pipes(lst);
	do_heredoc(lst, gdata);
	handle_infile(lst, gdata);
	if (gdata->inf_err && !exists_pipe(lst))
		return ;
	handle_cmd(gdata, cmds);
}
