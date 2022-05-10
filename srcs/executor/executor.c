/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:17:54 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/10 13:06:24 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int handle_file(char *file, int type)
{
	int	fd;

	fd = 0;
	if (type == 2)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		return (-1);
	}
	return (fd);
}

/*void	do_child_one(int fd, char *cmd, int *end, char **envp)
{
	close(end[0]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(end[1], STDOUT_FILENO);
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

void executor(t_gdata *gdata)
{
	t_dlist	*aux;
	int		tkn;
	char	*cmd;
	int		file;
	int		fd;

	aux = gdata->cmds_list;
	file = 0;
	fd = 0;
	tkn = 0;
	while (aux)
	{
		tkn = ((t_token_data *)aux->content)->token;
		cmd = ((t_token_data *)aux->content)->str;
		printf("TKN: %d\n", tkn);
		printf("CMD: %s\n", cmd);
		if (file && cmd)
			fd = handle_file(cmd, file);
		file = 0;
		if (is_file_token(tkn) && tkn != 3)
			file = 1;
		if (tkn == 1)
			file = 2; //indirection
		//if (cmd)
			//handle_cmd(fd, cmd, gdata->envp);
		aux = aux->next;
	}
}
