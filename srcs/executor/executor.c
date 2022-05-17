/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:17:54 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/17 15:48:20 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	need_cmd_slash(char *cmd)
{
	int	r;

	r = 1;
	if (cmd[0] == '/' || cmd[0] == '.' || cmd[0] == '~')
		r = 0;
	return (r);
}


char *cmd_add_slash(char *cmd)
{
	int		l;
	int		i;
	char	*n_cmd;

	l = ft_strlen(cmd);
	n_cmd = malloc(sizeof(char) * (l + 2));
	if (!n_cmd)
		return (0);
	l = 1;
	i = 0;
	n_cmd[0] = '/';
	while (cmd[i])
		n_cmd[l++] = cmd[i++];
	n_cmd[l] = '\0';
	return (n_cmd);
}

int handle_file_no_create(char *file)
{
	int	fd;

	printf("ABRO: %s\n", file);
	fd = open(file, O_RDONLY);
	printf("FD: %d\n", fd);
	if (fd < 0)
	{
		perror("Error1");
		return (-1);
	}
	return (fd);
}

int	handle_file_create(char *file)
{
	int fd;

	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error");
		return (-1);
	}
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
	//	write(2, "EJECUTAMOS\n", 11);
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

char	*command_parser(char *cmd)
{
	
}

int	handle_path(char *cmd, char **envp)
{
	int	i;
	char	*path;
	char	**all_paths;
	char	**mycmdargs;
	char	*cmd_one;

	if (need_cmd_slash(cmd))
		cmd = cmd_add_slash(cmd);
	i = path_index(envp);
	path = ft_strtrim(envp[i], "PATH=");
	all_paths = ft_split(path, ':');
	cmd = command_parser(cmd);
	mycmdargs = ft_split(cmd, ' ');
	if (check_access(cmd, mycmdargs, envp))
		return (1);
	i = -1;
	while (all_paths[++i])
	{
		cmd_one = ft_strjoin(all_paths[i], mycmdargs[0]);
		if (check_access(cmd_one, mycmdargs, envp))
			return (1);
		free(cmd_one);
	}
	perror("bash");
	exit(EXIT_FAILURE);
}

/*void	do_child_one(int fd, char *cmd, int *end, char **envp)
{
	close(end[0]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(end[1], STDOUT_FILENO);
	handle_path(cmd, envp);
}*/

/*void	do_child_one(int fd, char *cmd, int *end, char **envp)
{
	fd = fd +1;
	close(end[0]);
	dup2(end[1], STDOUT_FILENO);
	close(end[1]);
	handle_path(cmd, envp);
}*/

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

/*void	do_child_two(int fd, char *cmd, int *end, char **envp)
{
	close(end[1]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(end[0], STDOUT_FILENO);
	handle_path(cmd, envp);
}*/

/*void handle_cmd(int in, int *end, char *cmd, char **envp)
{
	pid_t	p1;
	//pid_t	p2;
	int		status;

	p1 = fork();
	if (p1 < 0)
		return (perror("Fork: "));
	if (p1 == 0)
		do_child_one(in, cmd, end, envp);
	close(end[1]);
	waitpid(p1, &status, 0);
	if (WEXITSTATUS(status))
	{
		printf("WEXITSTATUS1: %d\n", status);
		return ;
	}
	write(2, "SIGO\n", 5);
	char *out = malloc(sizeof(char) * 4096);
	out = get_next_line(end[0]);
	write(2, out, ft_strlen(out));
	write(2, "\n", 1);
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
}*/

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

int	open_next_file(t_dlist *lst)
{
	t_dlist	*aux;
	char	*cmd;

	aux = lst;

	aux = aux->next;
	if (!aux)
		return (-1);
	aux = aux->next;
	if (!aux)
		return (-1);
	cmd = (((t_token_data *)aux->content)->str);
	return (handle_file_create(ft_strtrim(cmd, " ")));
}

void do_child_one(int fd, int *end, char *cmd, char **envp)
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
	if (p1 < 0)
		return (perror("Fork: "));
	if (p1 == 0)
		do_child_one(fd, end, cmd, envp);
	close(end[1]);
	waitpid(p1, &status, 0);
	if (WEXITSTATUS(status))
	{
		write(2, "WEXIT1\n", 7);
		return ;
	}
	char *out;
	out = get_next_line(end[0]);
	while (out)
	{
		printf("%s", out);
		out = get_next_line(end[0]);
	}
	//out = remove_new_line(out);
	close(end[0]);
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

void	do_child_two(int fd, int *end, char *cmd, char **envp)
{
	close(end[1]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(end[0], STDIN_FILENO);
	handle_path(cmd, envp);
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

void executor(t_gdata *gdata)
{
	t_dlist	*aux;
	int		tkn;
	char	*cmd;
	int		file;
	int		fd[2];
	int		end[2];
	int		next_type;

	aux = gdata->cmds_list;
	ft_printdlst(aux);
	file = 0;
	fd[0] = 0;
	fd[1] = 1;
	tkn = 0;
	next_type = 0;
	pipe(end);
	//printf("COMMANDS: %d\n", gdata->commands);
	while (aux && gdata->commands > 0)
	{
		tkn = ((t_token_data *)aux->content)->token;
		cmd = ft_strtrim((((t_token_data *)aux->content)->str), " ");
		cmd = ft_strtrim(cmd, " ");
		if (file && cmd)
			fd[0] = handle_file_no_create(cmd);
		if (is_file_token(tkn) && tkn != 3)
			file = 1;
		//if (tkn == 2 || tkn == 4)
		//	file = 2; //indirection
	//	printf("TKN: %d\n", tkn);
	//	printf("CMD: %s\n", cmd);
		if (!file && cmd)
		{
			next_type = get_next_type(aux);
			printf("next_type: %d\n", next_type);
			if (next_type)
				fd[1] = open_next_file(aux);
			if (next_type == -1)
				handle_cmd3(0, end, cmd, gdata->envp);
			else if (next_type == 0)
				handle_cmd1(fd[0], end, cmd, gdata->envp);
			else if (next_type == 1)
				handle_cmd2(fd[1], end, cmd, gdata->envp);
			//handle_cmd(fd, end, cmd, gdata->envp);
			//close(end[0]);
			//close(end[1]);
			gdata->commands--;
		}
		if (cmd && file > 0)
			file = 0;
		aux = aux->next;
	}
}
