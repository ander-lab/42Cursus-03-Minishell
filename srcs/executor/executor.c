/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:17:54 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/09 13:36:29 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_next_type(t_dlist *lst)
{
	t_dlist	*aux;
	int		tkn;

	aux = lst;
	aux = aux->next;
	if (!aux)
		return (-1);
	tkn = ((t_token_data *)aux->content)->token;
	return (tkn);
}

int	get_prev_type(t_dlist *lst)
{
	t_dlist	*aux;	
	int		tkn;

	aux = lst;
	aux = aux->prev;
	if (!aux)
		return (-1);
	tkn = ((t_token_data *)aux->content)->token;
	return (tkn);
}

static t_dlist	*handle_executor(t_gdata *gdata, t_dlist *lst, int *end)
{
	int	next_type;
	int	prev_type;
	char	*cmd;
	int		tkn;

	next_type = get_next_type(lst);
	prev_type = get_prev_type(lst);
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	cmd = ft_strtrim(cmd, " ");
	tkn = ((t_token_data *)lst->content)->token;
	printf("TKN: %d\n", tkn);
	printf("CMD: %s\n", cmd);
	if (next_type == 0)	//pipe
	{
		printf("TIPO1\n");
		printf("MANDO CMD: %s\n", cmd);
		printf("FD: %d\n", gdata->fd[0]);
		handle_cmd1(gdata->fd[0], end, cmd, gdata->envp);
	}
	else if (next_type == 2 || next_type == 4 || prev_type == 2)	//redirección
	{
		printf("TIPO2\n");
		lst = do_red_or_app(lst, gdata);
		if (gdata->fd[1] == -1)
			return (0);
		if (prev_type != 3)
			handle_cmd2(gdata->fd[1], end, cmd, gdata->envp);
	}
	//else if (next_type == -1)		//un cmd
	else
	{
		printf("TIPO3\n");
		handle_cmd3(0, end, cmd, gdata->envp);
		lst = lst->next;
	}
	gdata->commands--;
	return (lst);
}

static void	handle_here(t_dlist *lst, t_gdata *gdata)
{
	int	tkn;

	while (exists_heredoc(lst))
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
			do_heredoc(lst, gdata);
		lst = lst->next;
	}
}

void	handle_infile(t_dlist *lst, t_gdata *gdata)
{
	int	tkn;

	while (lst && !gdata->err)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 1)
			do_infile(lst, gdata);
		lst = lst->next;
	}
}

t_dlist	*iter_indirection(t_dlist *lst)
{
	int	tkn;
	
	tkn = ((t_token_data *)lst->content)->token;
	while (tkn == 1)
	{
		lst = lst->next;
		lst = lst->next;
		if (!lst)
			return (0);
		tkn = ((t_token_data *)lst->content)->token;
	}
	return (lst);
}

t_dlist	*iter_to_last_heredoc(t_dlist *lst)
{
	int		tkn;
	t_dlist	*aux;

	aux = lst;
	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
			aux = lst->next->next;
		lst = lst->next;
	}
	return (aux);
}

t_dlist	*iter_to_cmd(t_dlist *lst)
{
	lst = iter_to_last_heredoc(lst);
	if (!lst)
		return (0);
	lst = iter_indirection(lst);
	return (lst);
}

/*int		ends_in_heredoc(t_dlist	*lst)
{
	int	ends;
	int	tkn;

	ends = 0;
	while (lst && !ends)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
		{
			if (!lst->next->next)
				ends = 1;
		}
		lst = lst->next;
	}
	return (ends);
}*/

void	executor(t_gdata *gdata)
{
	t_dlist	*lst;
	int		end[2];

	lst = gdata->cmds_list;
	pipe(end);
	handle_here(lst, gdata);
	handle_infile(lst, gdata);
	if (gdata->err)
		return ;
	lst = iter_to_cmd(lst);
	if (!lst)
		return ;
	while (lst)
	{
		lst = handle_executor(gdata, lst, end);
	}
	/*while (lst && gdata->commands > 0)
	{
		char* cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
		tkn = ((t_token_data *)lst->content)->token;
		printf("CMD0: %s\n", cmd);
		printf("TKN0: %d\n", tkn);*/
	//	lst = handle_executor(gdata, lst, end);
		/*if (is_infile(lst))
			lst = do_infile(lst, gdata);
		else
			lst = handle_executor(gdata, lst, end);*/
	//}
}
