/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:48:58 by goliano-          #+#    #+#             */
/*   Updated: 2022/09/20 12:08:20 by goliano-         ###   ########.fr       */
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

void	check_expansion(t_cmds *cmds)
{
	char	*cmd;
	int		x;
	int		qt;
	int		fq;

	x = 0;
	fq = 0;
	cmd = (char *)cmds->content;
	if (!cmd)
		return ;
	while (cmd[x])
	{
		qt = is_quote(cmd[x]);
		if (qt > 0 && fq == 0)
			fq = qt;
		else if (qt == fq)
			fq = 0;
		if (cmd[x] == '$' && (fq == 1 || fq == 0))
			cmds->exp = 1;
		if (cmd[x] == '$' && cmd[x + 1] == '?')
			cmds->exp = 0;
		x++;
	}
}

void	cmds_iteration(t_cmds *cmds, t_gdata *gdata)
{
	char	*cmd;

	while (cmds)
	{
		cmd = (char *)cmds->content;
		check_expansion(cmds);
		if (ft_strstr(cmd, "echo"))
			cmds->content = remove_quotes(cmd);
		if (cmds->exp)
			cmds->content = handle_expansion(cmds, gdata->env->envp);
		cmds = cmds->next;
	}
}

void	executor(t_gdata *gdata, int i)
{
	t_dlist	*lst;
	t_cmds	*cmds;

	cmds = gdata->cmds_lst;
	cmds_iteration(cmds, gdata);
	lst = gdata->glob_lst;
	if (gdata->n_pipes > 0)
		gdata->prev_n_pipes = gdata->n_pipes;
	gdata->n_pipes = get_n_pipes(lst);
	do_heredoc(lst, gdata);
	handle_infile(lst, gdata);
	if (gdata->inf_err && !exists_pipe(lst))
		return ;
	handle_cmd(gdata, cmds, i);
}
