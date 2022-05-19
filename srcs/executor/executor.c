/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:17:54 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/19 15:41:17 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_next_type(t_dlist *lst)
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
			if (next_type == 1)
				fd[1] = open_next_file(aux, 0);
			else if (next_type == 2)
				fd[1] = open_next_file(aux, 1);
			if (next_type == -1)		//un cmd
				handle_cmd3(0, end, cmd, gdata->envp);
				//handle_path(cmd, gdata->envp);
			else if (next_type == 0)	//pipe
				handle_cmd1(fd[0], end, cmd, gdata->envp);
			else if (next_type == 1)	//redirección
				handle_cmd2(fd[1], end, cmd, gdata->envp);
			else if (next_type == 2)	//append
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
