/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:35:02 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/05 16:01:23 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_child(int **fd, int r, t_gdata *gdata)
{
	int	s;

	s = 0;
	if (r != gdata->n_pipes)
		dup2(fd[r][WRITE_END], STDOUT_FILENO);
	if (r != 0)
		dup2(fd[r - 1][READ_END], STDIN_FILENO);
	while (s < gdata->n_pipes)
	{
		close(fd[s][READ_END]);
		close(fd[s][WRITE_END]);
		s++;
	}
}

void	handle_cmd(t_gdata *gdata, t_cmds *cmds_lst)
{
	int **fd;

	fd = ft_calloc(sizeof(int *), gdata->n_pipes);
	int i = 0;
	int status;
	while (i < gdata->n_pipes)
	{
		fd[i] = ft_calloc(sizeof(int), 2);
		pipe(fd[i]);
		i++;
	}
	int r = -1;
	int *pids;
	pids = ft_calloc(sizeof(int), gdata->n_pipes + 1);
	while (++r < gdata->n_pipes + 1)
	{
		pids[r] = fork();
		if (pids[r] == -1)
		{
			perror("Fork: ");
			exit(EXIT_FAILURE);
		}
		if (pids[r] == 0)
		{
			do_child(fd, r, gdata);
			write(2, "mando\n", 6);
			write(2, cmds_lst->content, ft_strlen(cmds_lst->content));
			write(2, "\n", 1);
			handle_path(cmds_lst->content, gdata->envp);
		}
		cmds_lst = cmds_lst->next;
	}
	int s = 0;
	while (s < gdata->n_pipes)
	{
		close(fd[s][READ_END]);
		close(fd[s][WRITE_END]);
		waitpid(pids[s], &status, 0);
		s++;
	}
	waitpid(pids[s], &status, 0);
}
