/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:32:42 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/01 16:41:52 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	here_cmd_exec(/*int fd,*/ int *end, char *cmd, t_gdata *gdata)
{
	close(end[1]);
	//dup2(fd, STDOUT_FILENO);
	//close(fd);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	handle_path(cmd, gdata->envp);
}

t_dlist	*go_to_pipe(t_dlist *lst)
{
	int	tkn;

	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 0)
			return (lst->next);
		lst = lst->prev;
	}
	return (lst);
}

t_dlist	*go_to_cmd(t_dlist *lst)
{
	t_dlist *aux;
	int	tkn;
	//char *cmd;

	aux = go_to_pipe(lst);
	if (aux)
		return (aux);
	lst = lst->prev;
	lst = lst->prev;
	if (!lst->prev)
		return (lst);
	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
		{
			aux = lst->next;
			aux = aux->next;
			tkn = ((t_token_data *)aux->content)->token;
			while (tkn == 1)
			{
				aux = aux->next;
				aux = aux->next;
				tkn = ((t_token_data *)aux->content)->token;
			}
		//	cmd = ft_strtrim((((t_token_data *)aux->content)->str), " ");
			if (tkn != 3)
				return (aux);
		}
		lst = lst->prev;
	}
	lst = lst->next;
	return (lst->next);
}

t_dlist *go_last_here(t_dlist *lst)
{
	t_dlist	*aux;
	int	tkn;

	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
		{
			aux = lst;
			while (lst)
			{
				tkn = ((t_token_data *)lst->content)->token;
				if (tkn == 3)
					break ;
				lst = lst->next;
			}
			lst = aux;
		}
		lst = lst->next;
	}
	return (aux->next);
}

void	do_here_cmd(t_dlist *lst, t_gdata *gdata)
{
	char	*cmd;
	char	*here;
	int		end[2];
	pid_t	p;
	int	status;
	int	next_type;

	lst = go_to_cmd(lst);
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	printf("CMD: %s\n", cmd);
	next_type = get_next_type(lst);
	lst = go_last_here(lst);
	here = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	fill_heredoc(gdata, here);
	printf("NEXT: %d\n", next_type);
	//if (next_type == 2 || next_type == 4)
	//	lst = do_red_or_app(lst, gdata);
	pipe(end);
	write(end[1], gdata->heredoc, ft_strlen(gdata->heredoc));
	p = fork();
	status = 0;
	if (p < 0)
		write(2, "error\n", 6);
	if (p == 0)
		here_cmd_exec(/*gdata->fd[1],*/ end, cmd, gdata);
	close(end[0]);
	close(end[1]);
	waitpid(p, &status, 0);
	if (WEXITSTATUS(status))
	{
		write(2, "WEXIT1\n", 7);
	}
}

void	do_heredoc(t_dlist *lst, t_gdata *gdata)
{
	char	*cmd;

	lst = go_heredoc(lst);
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	if (has_quotes(cmd))
		cmd = cpy_str_no_quotes(cmd);
	printf("NEED: %d\n", need_exec(lst));
	return ;
	if (is_last_heredoc(lst)/* && need_exec(lst)*/)
		do_here_cmd(lst, gdata);
	else
		fill_heredoc(gdata, cmd);
}
