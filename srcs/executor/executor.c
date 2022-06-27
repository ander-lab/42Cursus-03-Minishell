/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:17:54 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/20 16:21:03 by goliano-         ###   ########.fr       */
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

/*static t_dlist	*handle_executor(t_gdata *gdata, t_dlist *lst)
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
}*/

/*static t_dlist	*go_to_pipe(t_dlist *lst)
{
	int	tkn;

	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 0)
			return (lst->next);
		lst = lst->next;
	}
	return (lst);
}*/

/*static	int	exists_pipe(t_dlist *lst)
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
}*/

/*static t_dlist *red_app_handler_back(t_dlist *lst, t_gdata *gdata)
{
	char	*file;
	int	tkn;

	file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	if (lst->prev)
		lst = lst->prev;
	tkn = ((t_token_data *)lst->content)->token;
	if (tkn != 2 && tkn != 4)
		return (lst->next);
	while (tkn == 2 || tkn == 4)
	{
		if (tkn == 2)
			gdata->fd[1] = handle_file_create(file, 0);
		else if (tkn == 4)
			gdata->fd[1] = handle_file_create(file, 1);
		if (lst->prev)
			lst = lst->prev;
		file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
		if (lst->prev)
			lst = lst->prev;
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn != 2 && tkn != 4)
			return (lst->next);
	}
	return (lst);
}*/

/*static t_dlist *handle_one_cmd(t_dlist *lst, t_gdata *gdata)
{
	char	*cmd;
	
	lst = do_infile(lst, gdata);
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	lst = red_app_handler(lst, gdata);
	handle_cmd2(gdata, cmd);
	if (lst)
		lst = lst->next;
	return (lst);
}*/

/*static t_dlist	*handle_executor(t_gdata *gdata, t_dlist *lst, int *end)
{
	//int	next_type;
	int	prev_type;
	char	*cmd;
	int		tkn;
	int	prev_pipe;

	//next_type = get_next_type(lst);
	gdata->fd_pipe = gdata->fd[READ_END];
	printf("GDATA FD PIPE: %d\n", gdata->fd_pipe);
	pipe(gdata->end);
	printf("END[0]: %d\n", gdata->end[READ_END]);
	printf("END[1]: %d\n", gdata->end[WRITE_END]);
	prev_pipe = 0;
	prev_type = get_prev_type(lst);
	if (prev_type == 0)
		prev_pipe = 1;
	lst = do_infile(lst, gdata);
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	tkn = ((t_token_data *)lst->content)->token;
	printf("TKN0: %d\n", tkn);
	printf("CMD0: %s\n", cmd);
	lst = red_app_handler(lst, gdata);
	printf("FD[0]: %d\n", gdata->fd[0]);
	printf("FD[1]: %d\n", gdata->fd[1]);
	printf("PREV_PIPE: %d\n", prev_pipe);
	handle_cmd1(gdata, cmd, prev_pipe, exists_pipe(lst));
	return (lst);*/
	/*else if (tkn != 6)
		lst = lst->next;
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	tkn = ((t_token_data *)lst->content)->token;
	printf("TKN1: %d\n", tkn);
	printf("CMD1: %s\n", cmd);
	lst = red_app_handler_back(lst, gdata);
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	tkn = ((t_token_data *)lst->content)->token;
	printf("TKN2: %d\n", tkn);
	printf("CMD2: %s\n", cmd);*/
	/*if (exists_pipe(lst))
	{
		handle_cmd1(gdata->fd[0], gdata, cmd);
	}
	else if (gdata->fd[1] > 2)
	{
		handle_cmd2(gdata->fd[1], end, cmd, gdata->envp);
	}*/
	/*if (tkn == 0)
	{
		handle_cmd1(gdata->fd[0], gdata, cmd);
	}
	else if (tkn > 5)
	{
		if (gdata->inf_err)
		{
			printf("INF ERROR\n");
			exit(0);
		}
		next_type = get_next_type(lst);
		if (next_type == 2 || next_type == 4)
		{
			cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
			lst = do_red_or_app(lst, gdata);
			handle_cmd2(gdata->fd[1], end, cmd, gdata->envp);
		}
	}
	//lst = do_pipes(lst);
	char *cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	printf("TKN1: %d\n", tkn);
	printf("CMD1: %s\n", cmd);*/
	/*if (next_type == 0)	//pipe
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
	return (lst);*/
//}

/*static void	handle_here(t_dlist *lst, t_gdata *gdata)
{
	int	tkn;

	while (exists_heredoc(lst))
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
			do_heredoc(lst, gdata);
		lst = lst->next;
	}
}*/

/*void	handle_infile(t_dlist *lst, t_gdata *gdata)
{
	int	tkn;

	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 1)
			infile_checker(lst, gdata);
		lst = lst->next;
	}
}*/

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

int	get_n_pipes(t_dlist *lst)
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
	
	
	//int		end[2];
	//int		tkn;

	lst = gdata->cmds_list;
	gdata->n_pipes = get_n_pipes(lst);
	
	
	//pipe(end);
	
	/*
	handle_here(lst, gdata);
	handle_infile(lst, gdata);
	*/
	
	
	//if (gdata->err)
	//	return ;
	//lst = iter_to_cmd(lst);
	//lst = iter_to_executor(lst);
	/*if (!lst)
		return ;*/
	/*char* cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	int tkn = ((t_token_data *)lst->content)->token;
	printf("CMD0: %s\n", cmd);
	printf("TKN0: %d\n", tkn);
	return ;*/
	
	
	/*printf("EXISTE: %d\n", exists_pipe(lst));
	if (!exists_pipe(lst))
	{
		printf("CASO1\n");
		lst = handle_one_cmd(lst, gdata);
	}*/


	handle_cmd1(gdata);
	/*while (lst)
	{
		lst = handle_executor(gdata, lst);
		lst = go_to_pipe(lst);
		gdata->fd[0] = -1;
		gdata->fd[1] = -1;
		char* cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
		int tkn = ((t_token_data *)lst->content)->token;
		printf("CMD5: %s\n", cmd);
		printf("TKN5: %d\n", tkn);
	}*/
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
