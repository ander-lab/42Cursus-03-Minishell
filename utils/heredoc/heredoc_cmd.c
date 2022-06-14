/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:08:39 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/14 16:16:19 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	here_cmd_exec(int fd, int *end, char *cmd, t_gdata *gdata)
{
	close(end[1]);
	if (fd >= 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	handle_path(cmd, gdata->envp);
}

void	here_cmd_call(t_gdata *gdata, char *cmd, int red)
{
	int		end[2];
	pid_t	p;
	int		status;

	pipe(end);
	write(end[1], gdata->heredoc, ft_strlen(gdata->heredoc));
	p = fork();
	status = 0;
	if (p < 0)
		write(2, "error\n", 6);
	if (p == 0)
	{
		if (red)
			here_cmd_exec(gdata->fd[1], end, cmd, gdata);
		else
			here_cmd_exec(-1, end, cmd, gdata);
	}
	close(end[0]);
	close(end[1]);
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

void	do_here_cmd(t_dlist *lst, t_gdata *gdata)
{
	char	*cmd;
	char	*here;
	int		red;
	t_dlist	*aux;

	aux = lst;
	lst = go_to_cmd(lst);
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	red = red_app_handler(aux, gdata);
	lst = go_last_here(lst);
	here = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	fill_heredoc(gdata, here);
	cmd = check_fill_cmd(lst, cmd);
	here_cmd_call(gdata, cmd, red);
}
