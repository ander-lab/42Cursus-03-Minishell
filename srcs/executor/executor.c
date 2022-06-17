/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:17:54 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/17 16:30:59 by goliano-         ###   ########.fr       */
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

static t_dlist	*handle_executor(t_gdata *gdata, t_dlist *lst)
{
	int	next_type;
	char	*cmd;
	int		tkn;

	tkn = ((t_token_data *)lst->content)->token;
	if (tkn == 0)
		lst = lst->next;
	else if (tkn == 1)
		lst = do_infile(lst, gdata);
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	next_type = get_next_type(lst);
	if (next_type == 0)	//pipe
	{
		handle_cmd1(gdata->fd[0], gdata, cmd);
		lst = lst->next;
		lst = lst->next;
	}
	else if (next_type == 2 || next_type == 4)	//redirección
	{
		lst = do_red_or_app(lst, gdata);
		if (gdata->fd[1] == -1)
			return (0);
		handle_cmd2(gdata->fd[1], gdata, cmd);
	}
	else
	{
		handle_cmd3(0, gdata, cmd);
		lst = lst->next;
	}
	if (gdata->err)
		exit(0);
	gdata->commands--;
	return (lst);
}

/*static t_dlist	*handle_executor(t_gdata *gdata, t_dlist *lst, int *end)
{
	int	next_type;
	int	prev_type;
	char	*cmd;
	//int		tkn;

	next_type = get_next_type(lst);
	prev_type = get_prev_type(lst);
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	//tkn = ((t_token_data *)lst->content)->token;
	//printf("TKN1: %d\n", tkn);
	//printf("CMD1: %s\n", cmd);
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
}*/

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
			infile_checker(lst, gdata);
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

t_dlist	*iter_red_app(t_dlist *lst)
{
	int	tkn;
	
	if (!lst)
		return (lst);
	tkn = ((t_token_data *)lst->content)->token;
	while (tkn == 2 || tkn == 4)
	{
		lst = lst->next;
		lst = lst->next;
		if (!lst)
			return (0);
		tkn = ((t_token_data *)lst->content)->token;
	}
	return (lst);
}

t_dlist	*iter_to_executor(t_dlist *lst)
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
	aux = iter_red_app(aux);
	return (aux);
}

/*t_dlist	*iter_to_cmd(t_dlist *lst)
{
	int	tkn;

	lst = iter_to_last_heredoc(lst);
	if (!lst)
		return (0);
	lst = iter_indirection(lst);
	lst = iter_red_app(lst);
	if (!lst)
		return (lst);
	tkn = ((t_token_data *)lst->content)->token;
	if (tkn == 0)
		lst = lst->next;
	return (lst);
}*/

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
	//int		end[2];
	//int		tkn;

	lst = gdata->cmds_list;
	//pipe(end);
	handle_here(lst, gdata);
	handle_infile(lst, gdata);
	if (gdata->err)
		return ;
	//lst = iter_to_cmd(lst);
	lst = iter_to_executor(lst);
	/*if (!lst)
		return ;*/
	/*char* cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	int tkn = ((t_token_data *)lst->content)->token;
	printf("CMD0: %s\n", cmd);
	printf("TKN0: %d\n", tkn);
	return ;*/
	while (lst)
	{
		lst = handle_executor(gdata, lst);
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
