/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:17:54 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/13 14:47:25 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int handle_file(char *file, int type)
{
	int	fd;

	fd = 0;
	if (type == 2)
	{
		file = ft_strtrim(file, " ");
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else
		fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		return (-1);
	}
	printf("ARCHIVO: %s abierto\n", file);
	return (fd);
}

static int check_access(char *cmd, char **mycmdargs, char **envp)
{
	int	r;

	r = 0;
	/*write(2, "CMD\n", 4);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\nANTES ACCESS\n", 14);
	int i = 0;
	while (mycmdargs[i])
	{
		write(2, "ARGS: \n", 7);
		write(2, mycmdargs[i], ft_strlen(mycmdargs[i]));
		write(2, "ARGS: \n", 7);
		i++;
	}*/
	if (access(cmd, X_OK) > -1)
	{
		execve(cmd, mycmdargs, envp);
		r = 1;
	}
	return (r);
}

static int	path_index(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (i);
}

int	handle_path(char *cmd, char **envp)
{
	int	i;
	char	*path;
	char	**all_paths;
	char	**mycmdargs;

	i = path_index(envp);
	path = ft_strtrim(envp[i], "PATH=");
	all_paths = ft_split(path, ':');
	mycmdargs = ft_split(cmd, ' ');
	if (check_access(cmd, mycmdargs, envp))
		return (1);
	perror("zsh");
	exit(EXIT_FAILURE);
}

void	do_child_one(int fd, char *cmd, int *end, char **envp)
{
	close(end[0]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(end[1], STDOUT_FILENO);
	handle_path(cmd, envp);
}

/*int	pipex(int fd, char *cmd, char **envp)
{
	int	end[2];
	pid_t	p1;
	pid_t	p2;
	int		status;

	pipe(end);
	p1 = fork();
	if (p1 < 0)
		return (perror("Fork: "));
	if (p1 == 0)
		do_child_one(fd, cmd, end, envp);
	waitpid(p1, &status, 0);
	if (WEXITSTATUS(status))
		return ;
}*/

void	do_child_two(int fd, char *cmd, int *end, char **envp)
{
	close(end[1]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(end[0], STDOUT_FILENO);
	handle_path(cmd, envp);
}

void handle_cmd(int in, int *end, char *cmd, char **envp)
{
	pid_t	p1;
	pid_t	p2;
	int		status;

	p1 = fork();
	if (p1 < 0)
		return (perror("Fork: "));
	if (p1 == 0)
		do_child_one(in, cmd, end, envp);
	waitpid(p1, &status, 0);
	if (WEXITSTATUS(status))
	{
		printf("WEXITSTATUS1: %d\n", status);
		return ;
	}
	p2 = fork();
	if (p2 < 0)
		return (perror("Fork: "));
	if (p2 == 0)
		do_child_two(in, cmd, end, envp);
	close(end[0]);
	close(end[1]);
	waitpid(p2, &status, 0);
	if (WEXITSTATUS(status))
	{
		printf("WEXITSTATUS2: %d\n", status);
		return ;
	}
	return ;
}

int	get_next_type(t_dlist *lst)
{
	t_dlist	*aux;
	int		tkn;
	int		type;

	aux = lst;
	aux = aux->next;
	type = 0;
	if (!aux)
		return (-1);
	tkn = ((t_token_data *)aux->content)->token;
	if (tkn == 0)			//viene commando (pipe)
		type = 0;
	else if (tkn == 2)		//viene redireccion (>)
		type = 1;
	else if (tkn == 4)		//viene append (>>)
		type = 2;
	return (type);
}

void executor(t_gdata *gdata)
{
	t_dlist	*aux;
	int		tkn;
	char	*cmd;
	int		file;
	int		fd;
	int		end[2];
	int		next_type;

	aux = gdata->cmds_list;
	file = 0;
	fd = 0;
	tkn = 0;
	next_type = 0;
	printf("COMMANDS: %d\n", gdata->commands);
	while (aux)
	{
		tkn = ((t_token_data *)aux->content)->token;
		cmd = ((t_token_data *)aux->content)->str;
		if (file && cmd)
			fd = handle_file(cmd, file);
		if (is_file_token(tkn) && tkn != 3)
			file = 1;
		if (tkn == 2 || tkn == 4)
			file = 2; //indirection
		printf("TKN: %d\n", tkn);
		printf("CMD: %s\n", cmd);
		if (!file && cmd)
		{
			next_type = get_next_type(aux);
			return ;
			cmd = ft_strtrim(cmd, " ");
			pipe(end);
			handle_cmd(fd, end, cmd, gdata->envp);
			close(end[0]);
			close(end[1]);
		}
		if (cmd && file > 0)
			file = 0;
			//handle_cmd(fd, cmd, gdata->envp);
		aux = aux->next;
	}
}
