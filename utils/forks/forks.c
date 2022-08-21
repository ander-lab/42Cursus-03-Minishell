/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:45:54 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/20 20:23:16 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_child(t_cmds *cmds, int r, t_gdata *gdata)
{
	int	s;

	s = 0;
	if (r != gdata->n_pipes)
		dup2(gdata->fd[r][WRITE_END], STDOUT_FILENO);
	if (r != 0)
		dup2(gdata->fd[r - 1][READ_END], STDIN_FILENO);
	if (cmds->ind > 0)
	{
		dup2(cmds->ind, STDIN_FILENO);
		close(cmds->ind);
	}
	if (cmds->red > 0)
	{
		dup2(cmds->red, STDOUT_FILENO);
		close(cmds->red);
	}
	while (s < gdata->n_pipes)
	{
		close(gdata->fd[s][READ_END]);
		close(gdata->fd[s][WRITE_END]);
		s++;
	}
}

int	**init_fds(t_gdata *gdata)
{
	int	**fd;
	int	i;

	fd = ft_calloc(sizeof(int *), gdata->n_pipes);
	i = 0;
	if (!fd)
		return (0);
	while (i < gdata->n_pipes)
	{
		fd[i] = ft_calloc(sizeof(int), 2);
		if (!fd[i])
			return (0);
		pipe(fd[i]);
		i++;
	}
	return (fd);
}

void	handle_here_exec(t_cmds *cmds, t_gdata *gdata, int r)
{
	int		fd;
	char	*join;

	if (cmds->here)
	{
		fd = open("42heredoctmpfile", O_WRONLY | O_CREAT, 0644);
		if (fd < 0)
		{
			perror("42heredoctmpfile: ");
			exit(0);
		}
		write(fd, gdata->heredoc[r], ft_strlen(gdata->heredoc[r]));
		join = ft_strjoin_space(cmds->content, "42heredoctmpfile");
		handle_path(join, gdata->env->envp);
	}
	else
		handle_path(cmds->content, gdata->env->envp);
}

void	close_fds(t_gdata *gdata, int *pids)
{
	int	s;
	int	status;

	s = 0;
	if (access("42heredoctmpfile", F_OK) == 0)
		unlink("42heredoctmpfile");
	while (s < gdata->n_pipes)
	{
		close(gdata->fd[s][READ_END]);
		close(gdata->fd[s][WRITE_END]);
		s++;
	}
	s = 0;
	while (s < gdata->n_pipes)
	{
		waitpid(pids[s], &status, 0);
		s++;
	}
	waitpid(pids[s], &status, 0);
	if (WIFEXITED(status))
		s_glob.proc = WEXITSTATUS(status);
}

int	check_builtin(t_gdata *gdata, t_cmds *cmds)
{
	int		it_is;
	char	*cmd;

	it_is = 0;
	cmd = (char *)cmds->content;
	if (is_builtin(cmd))
	{
		it_is = 1;
		execute_builtin(cmds, gdata);
	}
	return (it_is);
}
