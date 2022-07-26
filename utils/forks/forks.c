/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:35:02 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/26 11:55:42 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_child(t_cmds *cmds, int **fd, int r, t_gdata *gdata)
{
	int	s;

	s = 0;
	if (r != gdata->n_pipes)
		dup2(fd[r][WRITE_END], STDOUT_FILENO);
	if (r != 0)
		dup2(fd[r - 1][READ_END], STDIN_FILENO);
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
		close(fd[s][READ_END]);
		close(fd[s][WRITE_END]);
		s++;
	}
}

static int	**init_fds(t_gdata *gdata)
{
	int	**fd;
	int	i;

	fd = ft_calloc(sizeof(int *), gdata->n_pipes);
	i = 0;
	while (i < gdata->n_pipes)
	{
		fd[i] = ft_calloc(sizeof(int), 2);
		pipe(fd[i]);
		i++;
	}
	return (fd);
}

static void	handle_here_exec(t_cmds *cmds, t_gdata *gdata, int r)
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
		handle_path(join, gdata->envp);
	}
	else
		handle_path(cmds->content, gdata->envp);
}

static void	close_fds(t_gdata *gdata, int *pids, int **fd)
{
	int	s;
	int	status;

	s = 0;
	if (access("42heredoctmpfile", F_OK) == 0)
		unlink("42heredoctmpfile");
	while (s < gdata->n_pipes)
	{
		close(fd[s][READ_END]);
		close(fd[s][WRITE_END]);
		waitpid(pids[s], &status, 0);
		s++;
	}
	// cerrar cmds->ind, cmds->red
	waitpid(pids[s], &status, 0);
	if (WIFEXITED(status))
	{
		//int val = WEXITSTATUS(status);
		//printf("VAL: %d\n", val);
	}
	/*printf("STAT: %d\n", status);
	printf("WIF: %d\n", WIFEXITED(status));
	printf("WEXIT: %d\n", WEXITSTATUS(status));*/
}

int	check_builtin(t_gdata *gdata, t_cmds *cmds)
{
	char	*cmd;
	int		it_is;

	it_is = 0;
	cmd = (char *)cmds->content;
	if (is_builtin(cmd))
		execute_builtin(gdata, cmd);
	return (it_is);
}

void	handle_cmd(t_gdata *gdata, t_cmds *cmds)
{
	int		**fd;
	int		r;
	int		*pids;
	char	*cmd;

	r = -1;
	fd = init_fds(gdata);
	pids = ft_calloc(sizeof(int), gdata->n_pipes + 1);
	while (++r < gdata->n_pipes + 1)
	{
		cmd = (char *)cmds->content;
		if (is_builtin(cmd))
		{
			execute_builtin(gdata, cmd);
		}
		else
		{
			pids[r] = fork();
			if (pids[r] == -1)
			{
				perror("Fork: ");
				exit(EXIT_FAILURE);
			}
			if (pids[r] == 0)
			{
				do_child(cmds, fd, r, gdata);
				handle_here_exec(cmds, gdata, r);
			}
		}
		cmds = cmds->next;
	}
	close_fds(gdata, pids, fd);
}
