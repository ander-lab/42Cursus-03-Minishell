/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:35:02 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/01 13:24:16 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_child_two(int fd, int *end, char *cmd, char **envp)
{
	close(end[1]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(end[0], STDIN_FILENO);
	handle_path(cmd, envp);
}

static void do_child_one(int fd, int *end, char *cmd, char **envp)
{
	close(end[0]);
	dup2(fd, STDIN_FILENO);	//fd es la entrada de execve
	close(fd);
	dup2(end[1], STDOUT_FILENO); //la salida de execve se guarda en end[1]
	//close(end[1]);
	handle_path(cmd, envp);
}

void handle_cmd3(int fd, int *end, char *cmd, char **envp)
{
	pid_t	p1;
	int	status;

	p1 = fork();
	fd += 1;
	end[0] += 1;
	if (p1 < 0)
		return (perror("Fork: "));
	if (p1 == 0)
		handle_path(cmd, envp);
	close(end[1]);
	waitpid(p1, &status, 0);
	if (WEXITSTATUS(status))
	{
		write(2, "WEXIT1\n", 7);
		return ;
	}
}

void handle_cmd1(int fd, int *end, char *cmd, char **envp)
{
	pid_t	p1;
	int	status;

	p1 = fork();
	if (p1 < 0)
		return (perror("Fork: "));
	if (p1 == 0)
		do_child_one(fd, end, cmd, envp);
	waitpid(p1, &status, 0);
	if (WEXITSTATUS(status))
	{
		write(2, "WEXIT1\n", 7);
		return ;
	}
}

void	handle_cmd2(int fd, int *end, char *cmd, char **envp)
{
	pid_t	p;
	int	status;

	p = fork();
	if (p < 0)
		return (perror("Fork: "));
	if (p == 0)
		do_child_two(fd, end, cmd, envp);
	close(end[0]);
	close(end[1]);
	waitpid(p, &status, 0);
	if (WEXITSTATUS(status))
	{
		write(2, "WEXIT2\n", 7);
		return ;
	}
}
