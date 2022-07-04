/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:35:02 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/04 14:20:52 by goliano-         ###   ########.fr       */
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

void	handle_cmd(t_gdata *gdata, t_dlist *lst)
{
	int **fd;

	fd = ft_calloc(sizeof(int *), gdata->n_pipes);
	while(lst)
	{
		printf("CMD: %s\n", ((t_token_data *)lst->content)->str);
		lst = lst->next;
	}
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
			handle_path(gdata->cmds[r], gdata->envp);
		}
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
