/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:35:02 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/20 16:21:01 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_child_two(t_gdata *gdata, char *cmd)
{
	if (gdata->fd[READ_END] > 2)
	{
		dup2(gdata->fd[READ_END], STDIN_FILENO);
		close(gdata->fd[READ_END]);
	}
	if (gdata->fd[WRITE_END] > 2)
	{
		dup2(gdata->fd[WRITE_END], STDOUT_FILENO);
		close(gdata->fd[WRITE_END]);
	}
	handle_path(cmd, gdata->envp);
	/*close(gdata->end[1]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(gdata->end[0], STDIN_FILENO);
	handle_path(cmd, gdata->envp);*/
}

/*static void do_child_one(t_gdata *gdata, char *cmd, int prev_pipe, int next_pipe)
{
	if (gdata->fd[READ_END] > 2)
	{
		printf("IND\n");
		dup2(gdata->fd[READ_END], STDIN_FILENO);
		close(gdata->fd[READ_END]);
	}
	else if (prev_pipe)
	{
		printf("PIPE LEC\n");
		printf("FD_PIPE: %d\n", gdata->fd_pipe);
		close(gdata->end[WRITE_END]);
		dup2(gdata->fd_pipe, STDIN_FILENO);
		close(gdata->fd_pipe);
	}
	if (gdata->fd[WRITE_END] > 2)
	{
		printf("RED\n");
		dup2(gdata->fd[WRITE_END], STDOUT_FILENO);
		close(gdata->fd[WRITE_END]);
	}
	else if (next_pipe)
	{
		printf("SAL PIPE\n");
		close(gdata->end[READ_END]);
		dup2(gdata->end[WRITE_END], STDOUT_FILENO);
		//close(gdata->end[1]);
	}
	handle_path(cmd, gdata->envp);
	*/
	/*close(gdata->end[0]);
	if (fd > 2)
	{
		dup2(fd, STDIN_FILENO);	//fd es la entrada de execve
		close(fd);
	}
	dup2(gdata->end[1], STDOUT_FILENO); //la salida de execve se guarda en end[1]
	//close(end[1]);
	handle_path(cmd, gdata->envp);*/
//}

void handle_cmd3(t_gdata *gdata, char *cmd)
{
	pid_t	p1;
	int	status;

	p1 = fork();
	if (p1 < 0)
		return (perror("Fork: "));
	if (p1 == 0)
		handle_path(cmd, gdata->envp);
	//close(g_fds[1][WRITE_END]);
	close(gdata->fd[WRITE_END]);
	waitpid(p1, &status, 0);
	if (WEXITSTATUS(status))
	{
		write(2, "WEXIT1\n", 7);
		return ;
	}
}

void handle_cmd1(t_gdata *gdata/*, char *cmd, int prev_pipe, int next_pipe*/)
{
	int	i;
	int	*pipes;

	i = 0;
	pipes = ft_calloc(sizeof(int), gdata->n_pipes * 2);
	while (i < gdata->n_pipes)
	{
		pipe(pipes + (i * 2));
		i++;
	}
	/*printf("PIPE[0]: %d\n", pipes[0]);
	printf("PIPE[1]: %d\n", pipes[1]);
	printf("PIPE[2]: %d\n", pipes[2]);
	printf("PIPE[3]: %d\n", pipes[3]);
	*/
	int cc = 0;
	int r = 0;
	int m;
	pid_t pid;
	while (gdata->cmds[r])
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Fork: ");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (r > 0)
			{
				/*int j = 0;
				while (j < gdata->n_pipes * 2)
				{
					if (j != (cc - 1) * 2 && j != cc * 2 + 1)
						close(pipes[j]);
					j++;
				}*/
				int op = (cc - 1) * 2;
				write(2, "STDIN\n", 6);
				ft_putnbr_fd(op, 2);
				write(2, "\n", 1);
				if (dup2(pipes[(cc - 1) * 2], STDIN_FILENO) < 0)
				{
					write(2, "error dup\n", 10);
					ft_putnbr_fd((cc - 1) * 2, 2);
					write(2, "\n", 1);
					perror("dup21");
					exit(EXIT_FAILURE);
				}
				//printf("TRABAJO1: %d\n", cc * 2 + 1);
			}
			if (r < gdata->commands - 1)
			{
				/*int k = 0;
				while (k < gdata->n_pipes * 2)
				{
					if (k != cc * 2 + 1 && k != (cc - 1) * 2)
						close(pipes[k]);
					k++;
				}*/
				int op = cc * 2 + 1;
				write(2, "STDOUT\n", 7);
				ft_putnbr_fd(op, 2);
				write(2, "\n", 1);
				if (dup2(pipes[cc * 2 + 1], STDOUT_FILENO) < 0)
				{
					perror("dup22");
					exit(EXIT_FAILURE);
				}
				//printf("TRABAJO2: %d\n", cc * 2 + 1);
			}
			int k = 0;
			while (k < gdata->n_pipes * 2)
			{
				if (k != cc * 2 + 1 && k != (cc - 1) * 2)
					close(pipes[k]);
				k++;
			}
			write(2, "ejecuto\n", 8);
			write(2, gdata->cmds[r], ft_strlen(gdata->cmds[r]));
			write(2, "\n", 1);
			handle_path(gdata->cmds[r], gdata->envp);
			exit(EXIT_SUCCESS);
		//	pid = wait(&j);
		}
		waitpid(pid, &m, 0);
		r++;
		cc++;
	}
	write(2, "FUERA\n", 6);
	int y = 0;
	while (y < gdata->n_pipes * 2)
	{
		close(pipes[y]);
		y++;
	}
	/*int status;
	for (int u = 0; u < gdata->n_pipes + 1; u++)
 	       wait(&status);
	      */
	/*pid_t	p1;
	int	status;

	p1 = fork();
	if (p1 < 0)
		return (perror("Fork: "));
	if (p1 == 0)
		do_child_one(gdata, cmd, prev_pipe, next_pipe);
	//close(gdata->end[0]);
	//close(g_fds[1][WRITE_END]);
	close(gdata->end[WRITE_END]);
	waitpid(p1, &status, 0);
	if (WEXITSTATUS(status))
	{
		write(2, "WEXIT1\n", 7);
		return ;
	}*/
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
