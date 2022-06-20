/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:08:39 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/20 10:02:36 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	here_cmd_exec(int fd, char *cmd, t_gdata *gdata)
{
	close(gdata->end[1]);
	if (fd >= 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	//else
	//	dup2(gdata->end[1], STDOUT_FILENO);
	dup2(gdata->end[0], STDIN_FILENO);
	close(gdata->end[0]);
	handle_path(cmd, gdata->envp);
	/*close(gdata->end[0]);
	dup2(fd, STDIN_FILENO);
	if (fd >= 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		dup2(gdata->end[1], STDOUT_FILENO);
	handle_path(cmd, gdata->envp);*/
}

static void	here_cmd_exec2(int fd, char *cmd, t_gdata *gdata)
{
	close(gdata->end[0]);
	dup2(gdata->end[1], STDIN_FILENO);
	close(gdata->end[1]);
	close(fd);
	//else
	//	dup2(gdata->end[1], STDOUT_FILENO);
	//dup2(gdata->end[1], STDOUT_FILENO);
	//close(gdata->end[0]);
	handle_path(cmd, gdata->envp);
	/*close(gdata->end[0]);
	dup2(fd, STDIN_FILENO);
	if (fd >= 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		dup2(gdata->end[1], STDOUT_FILENO);
	handle_path(cmd, gdata->envp);*/
}

void	here_cmd_call(t_gdata *gdata, char *cmd)
{
	//int		end[2];
	pid_t	p;
	int		status;

	//pipe(end);
	if (gdata->heredoc)
		write(gdata->end[1], gdata->heredoc, ft_strlen(gdata->heredoc));
	p = fork();
	status = 0;
	if (p < 0)
		write(2, "error\n", 6);
	if (p == 0)
	{
		/*if (red)
		{
			here_cmd_exec(gdata->fd[1], cmd, gdata);
		//	handle_cmd1(gdata->fd[1], gdata, cmd);
		}
		else
		{
			//handle_cmd2(gdata->fd[0], gdata, cmd);
			here_cmd_exec2(gdata->fd[0], cmd, gdata);
		}*/
		here_cmd_exec(gdata->fd[1], cmd, gdata);
		here_cmd_exec2(gdata->fd[0], cmd, gdata);
	}
	close(gdata->end[0]);
	close(gdata->end[1]);
	waitpid(p, &status, 0);
	if (WEXITSTATUS(status))
	{
		write(2, "WEXIT1\n", 7);
	}
}

char	*check_fill_cmd(t_dlist *lst, char *cmd)
{
	int		next_type;
	char	*next_cmd;
	char	*join;

	next_type = get_next_type(lst);
	if (next_type < 5)
		return (cmd);
	lst = lst->next;
	next_cmd = (((t_token_data *)lst->content)->str);
	join = ft_strjoin(cmd, next_cmd);
	free(cmd);
	free(next_cmd);
	return (join);
}

void	ind_handler(t_dlist *lst, t_gdata *gdata)
{
	int		tkn;
	int		ind;
	char	*file;
	
	ind = 0;
	while (lst)
	{
		tkn = (((t_token_data *)lst->content)->token);
		if (tkn == 1)
		{
			ind = 1;
			break ;
		}
		lst = lst->prev;
	}
	if (!ind)
		return ;
	lst = lst->next;
	file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	if (handle_file_no_create(file) < 0)
		gdata->err = 1;
}

void	do_here_cmd(t_dlist *lst, t_gdata *gdata)
{
	char	*cmd;
	char	*here;
	//int		red;
	t_dlist	*aux;

	aux = lst;
	lst = go_to_cmd(lst);
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	//red = red_app_handler(aux, gdata);
	lst = go_last_here(lst);
	here = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	fill_heredoc(gdata, here);
	ind_handler(aux, gdata);
	cmd = check_fill_cmd(lst, cmd);
	if (!gdata->err)
		here_cmd_call(gdata, cmd);
}
