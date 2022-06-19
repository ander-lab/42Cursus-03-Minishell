/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:35:02 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/17 10:08:47 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_child_two(t_gdata *gdata, char *cmd)
{
	if (gdata->fd[0] > 2)
	{
		dup2(gdata->fd[0], STDIN_FILENO);
		close(gdata->fd[0]);
	}
	if (gdata->fd[1] > 2)
	{
		dup2(gdata->fd[1], STDOUT_FILENO);
		close(gdata->fd[1]);
	}
	handle_path(cmd, gdata->envp);
	/*close(gdata->end[1]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(gdata->end[0], STDIN_FILENO);
	handle_path(cmd, gdata->envp);*/
}

static void do_child_one(t_gdata *gdata, char *cmd, int prev_pipe)
{
	if (gdata->fd[0] > 2)
	{
		printf("IND\n");
		dup2(gdata->fd[0], STDIN_FILENO);
		close(gdata->fd[0]);
	}
	else if (prev_pipe)
	{
		printf("PIPE LEC\n");
		close(gdata->end[1]);
		dup2(gdata->end[0], STDIN_FILENO);
		close(gdata->end[0]);
	}
	if (gdata->fd[1] > 2)
	{
		printf("RED\n");
		dup2(gdata->fd[1], STDOUT_FILENO);
		close(gdata->fd[1]);
	}
	else
	{
		printf("SAL PIPE\n");
		close(gdata->end[0]);
		dup2(gdata->end[1], STDOUT_FILENO);
		//close(gdata->end[1]);
	}
	handle_path(cmd, gdata->envp);
	/*close(gdata->end[0]);
	if (fd > 2)
	{
		dup2(fd, STDIN_FILENO);	//fd es la entrada de execve
		close(fd);
	}
	dup2(gdata->end[1], STDOUT_FILENO); //la salida de execve se guarda en end[1]
	//close(end[1]);
	handle_path(cmd, gdata->envp);*/
}

void handle_cmd3(t_gdata *gdata, char *cmd)
{
	pid_t	p1;
	int	status;

	p1 = fork();
	if (p1 < 0)
		return (perror("Fork: "));
	if (p1 == 0)
		handle_path(cmd, gdata->envp);
	//close(gdata->end[1]);
	waitpid(p1, &status, 0);
	if (WEXITSTATUS(status))
	{
		write(2, "WEXIT1\n", 7);
		return ;
	}
}

void handle_cmd1(t_gdata *gdata, char *cmd, int prev_pipe)
{
	pid_t	p1;
	int	status;

	p1 = fork();
	if (p1 < 0)
		return (perror("Fork: "));
	if (p1 == 0)
		do_child_one(gdata, cmd, prev_pipe);
	close(gdata->end[0]);
	waitpid(p1, &status, 0);
	if (WEXITSTATUS(status))
	{
		write(2, "WEXIT1\n", 7);
		return ;
	}
}

void	handle_cmd2(t_gdata *gdata, char *cmd)
{
	pid_t	p;
	int	status;

	p = fork();
	if (p < 0)
		return (perror("Fork: "));
	if (p == 0)
		do_child_two(gdata, cmd);
	/*close(gdata->end[0]);
	close(gdata->end[1]);*/
	waitpid(p, &status, 0);
	if (WEXITSTATUS(status))
	{
		write(2, "WEXIT2\n", 7);
		return ;
	}
}
