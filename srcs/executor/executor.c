/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 12:19:45 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/04 14:54:04 by goliano-         ###   ########.fr       */
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

void	init_quote_struct(t_quotes *qs)
{
	qs->fq = 0;
	qs->c = 0;
	qs->qw = 0;
}

void	quotes_handler(char *cmd, t_quotes *qs)
{
	int			i;
	int			qt;

	i = 0;
	init_quote_struct(qs);
	while (cmd[i])
	{
		qt = is_quote(cmd[i]);
		//printf("QT: %d\n", qt);
		//printf("FQ: %d\n", qs.fq);
		if (qt == qs->fq)
			qs->fq = 0;
		else if (qt != 0 && qs->fq != 0)
		{
			qs->qw = qt;
			qs->c++;
		}
		else if (qt > 0 && qs->fq == 0)
			qs->fq = qt;
		i++;
	}
}

size_t	cmd_length(char *cmd)
{
	size_t	l;
	int		i;

	i = 0;
	l = 0;
	while (cmd[i])
	{
		if (!is_quote(cmd[i]))
				l++;
		i++;
	}
	return (l);
}

void	*rewrite_quotes(char *cmd, t_quotes qs)
{
	char	*new;
	int		i;
	int		x;

	//printf("L: %d\n", cmd_length(cmd));
	new = ft_calloc(sizeof(char), cmd_length(cmd) + qs.c);
	i = 0;
	x = -1;
	while (cmd[i])
	{
		if (!is_quote(cmd[i]))
			new[++x] = cmd[i];
		else
		{
			if (qs.qw == 1)
				new[++x] = '\"';
			else
				new[++x] = '\'';
		}
		i++;
	}
	printf("CMD: %s\n", cmd);
	printf("qs.c: %zu\n", qs.c);
	printf("qw: %d\n", qs.qw);
	return (cmd);
}

void	handle_exp(t_cmds *cmds)
{
	t_quotes	qs;
	char		*cmd;

	while (cmds)
	{
		cmd = (char *)cmds->content;
		quotes_handler(cmd, &qs);
		cmds->content = rewrite_quotes(cmd, qs);
		cmds = cmds->next;
	}
}

void	executor(t_gdata *gdata)
{
	t_dlist	*lst;
	t_cmds	*cmds;

	//TODO -> Duplicar envp 
	//TODO -> Duplicar env keys
	//TODO -> LLamar a env to matrix y lst to env
	cmds = gdata->cmds_lst;
	handle_exp(cmds);
	lst = gdata->glob_lst;
	gdata->n_pipes = get_n_pipes(lst);
	do_heredoc(lst, gdata);
	handle_infile(lst, gdata);
	if (gdata->inf_err && !exists_pipe(lst))
		return ;
	handle_cmd(gdata, cmds);
//	while (cmds)
//	{
//		printf("CMD: %s\n", (char *)cmds->content);
//		printf("IND: %d\n", cmds->ind);
//		printf("RED: %d\n", cmds->red);
//		cmds = cmds->next;
//	}
}
