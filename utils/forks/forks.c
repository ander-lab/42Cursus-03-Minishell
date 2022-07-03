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

void	do_child(int **fd, int r, t_gdata *gdata)
{
	write(2, "count\n", 6);
	ft_putnbr_fd(gdata->n_pipes, 2);
	write(2, "\n", 1);
	if (r != gdata->n_pipes)
	{
		write(2, "STDOUT\n", 7);
		ft_putnbr_fd(fd[r][WRITE_END], 2);
		write(2, "\n", 1);
		dup2(fd[r][WRITE_END], STDOUT_FILENO);
	}
	if (r != 0)
	{
		write(2, "STDIN\n", 6);
		ft_putnbr_fd(fd[r - 1][READ_END], 2);
		write(2, "\n", 1);
		dup2(fd[r - 1][READ_END], STDIN_FILENO);
	}
	int s = 0;
	while (s < gdata->n_pipes)
	{
		close(fd[s][READ_END]);
		close(fd[s][WRITE_END]);
		s++;
	}
}

void	handle_cmd1(t_gdata *gdata)
{
	int **fd;

	fd = ft_calloc(sizeof(int *), gdata->n_pipes);
	int i = 0;
	while (i < gdata->n_pipes)
	{
		fd[i] = ft_calloc(sizeof(int), 2);
		pipe(fd[i]);
		i++;
	}
	/*int x = 0;
	while (x < gdata->n_pipes + 1)
	{
		pipe(fd[x]);
		x++;
	}*/
	printf("fd[0][0]: %d\n", fd[0][0]);
	printf("fd[0][1]: %d\n", fd[0][1]);
	//printf("fd[1][0]: %d\n", fd[1][0]);
	//printf("fd[1][1]: %d\n", fd[1][1]);
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
			write(2, "hijo\n", 5);
			/*if (r != gdata->n_pipes)
			{
				write(2, "STDOUT\n", 7);
				ft_putnbr_fd(r, 2);
				write(2, "\n", 1);
				dup2(fd[r][WRITE_END], STDOUT_FILENO);
			}
			if (r != 0)
			{
				write(2, "STDIN\n", 6);
				ft_putnbr_fd(r - 1, 2);
				write(2, "\n", 1);
				dup2(fd[r - 1][READ_END], STDIN_FILENO);
			}
			int s = 0;
			while (s < gdata->n_pipes)
			{
				close(fd[s][READ_END]);
				close(fd[s][WRITE_END]);
				s++;
			}*/
			do_child(fd, r, gdata);
			handle_path(gdata->cmds[r], gdata->envp);
			//execve(gdata->cmds[r], ft_split(gdata->cmds[r], ' '), gdata->envp);
			//return ;
			//exit(EXIT_SUCCESS);
		}
	}
	write(2, "padre\n", 6);
	int s = 0;
	int status;
	while (s < gdata->n_pipes)
	{
		close(fd[s][READ_END]);
		close(fd[s][WRITE_END]);
		waitpid(pids[s], &status, 0);
		printf("WIF %d: %d\n", s, WIFEXITED(status));
		printf("WEX %d: %d\n", s, WEXITSTATUS(status));
		s++;
	}
	waitpid(pids[s], &status, 0);
	printf("WIF20: %d\n", WIFEXITED(status));
	printf("WEX20: %d\n", WEXITSTATUS(status));
	//if (WEXITSTATUS(status))
	//	return ;
	/*int s = 0;
	while (s < gdata->n_pipes + 1)
	{
		if (s != gdata->n_pipes)
			close(fd[s][READ_END]);
		if (s != 0)
			close(fd[s][WRITE_END]);
		s++;
	}
	write(2, "hola7\n", 6);
	if (dup2(fd[0][WRITE_END], STDOUT_FILENO) < 0)
	{
		perror("Dup31: ");
		return ;
	}
	if (dup2(fd[gdata->n_pipes][READ_END], STDIN_FILENO) < 0)
	{
		perror("Dup32: ");
		return ;
	}
	handle_path(gdata->cmds[r], gdata->envp);
	write(2, "hola8\n", 6);
	close(fd[gdata->n_pipes][READ_END]);
	close(fd[0][WRITE_END]);
	*/
	/*int k = 0;
	int status;
	while (k < gdata->n_pipes)
	{
		waitpid(pids[k], &status, 0);
		k++;
	}
	write(2, "hola9\n", 6);
	write(2, "hola10\n", 7);*/
	/*int r = 0;
	int pid;
	while (r < gdata->n_pipes)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Fork: ");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			int k = 0;
			while (k < gdata->n_pipes + 1)
			{
				if (k == r)
					close(fd[k][WRITE_END]);
				else if (k == r + 1)
					close(fd[k][READ_END]);
				else
				{
					close(fd[k][WRITE_END]);
					close(fd[k][READ_END]);
				}
				k++;
			}
			write(2, "hola1\n", 6);
			if (dup2(fd[r][READ_END], STDIN_FILENO) < 0)
			{
				perror("dup21: ");
				exit(EXIT_FAILURE);
			}
			write(2, "hola2\n", 6);
			if (dup2(fd[r + 1][WRITE_END], STDOUT_FILENO) < 0)
			{
				perror("dup22: ");
				exit(EXIT_FAILURE);
			}
			write(2, "hola3\n", 6);
			close (fd[r][READ_END]);
			close (fd[r + 1][WRITE_END]);
			write(2, "hola4\n", 6);
			handle_path(gdata->cmds[r], gdata->envp);
		}
		write(2, "hola5\n", 6);
		r++;
	}*/
	/*int k = 0;
	while (k < gdata->n_pipes + 1)
	{
		if (k == 0)
			close(fd[k][READ_END]);
		else if (k == gdata->n_pipes)
			close(fd[k][WRITE_END]);
		else
		{
			close(fd[k][READ_END]);
			close(fd[k][WRITE_END]);
		}
		k++;
	}
	if (dup2(fd[0][WRITE_END], STDOUT_FILENO) < 0)
	{
		perror("dup24: ");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd[r][READ_END], STDIN_FILENO) < 0)
	{
		perror("dup23: ");
		exit(EXIT_FAILURE);
	}
	write(2, "hola6\n", 6);
	close(fd[0][WRITE_END]);
	close(fd[r][READ_END]);
	handle_path(gdata->cmds[r], gdata->envp);
	waitpid(pid, NULL, 0);*/
}

/*void handle_cmd1(t_gdata *gdata, char *cmd, int prev_pipe, int next_pipe)
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
				int j = 0;
				while (j < gdata->n_pipes * 2)
				{
					if (j != (cc - 1) * 2 && j != cc * 2 + 1)
						close(pipes[j]);
					j++;
				}
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
				int k = 0;
				while (k < gdata->n_pipes * 2)
				{
					if (k != cc * 2 + 1 && k != (cc - 1) * 2)
						close(pipes[k]);
					k++;
				}
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
				close(pipes[k]);
				k++;
			}
			write(2, "ejecuto\n", 8);
			write(2, gdata->cmds[r], ft_strlen(gdata->cmds[r]));
			write(2, "\n", 1);
			handle_path(gdata->cmds[r], gdata->envp);
			//exit(EXIT_SUCCESS);
		//	pid = wait(&j);
		}
		waitpid(pid, &m, 0);
		int y = 0;
		while (y < gdata->n_pipes * 2)
		{
			close(pipes[y]);
			y++;
		}
		r++;
		cc++;
	}
	printf("CC: %d\n", cc);
	write(2, "FUERA\n", 6);*/
	//int y = 0;
	/*while (y < gdata->n_pipes * 2)
	{
		close(pipes[y]);
		y++;
	}*/
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
//}

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
