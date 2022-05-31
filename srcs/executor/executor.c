/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:17:54 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/31 15:48:35 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_next_type(t_dlist *lst)
{
	t_dlist	*aux;
	int		tkn;

	aux = lst;
	aux = aux->next;
	if (!aux)
		return (-1);
	tkn = ((t_token_data *)aux->content)->token;
	return (tkn);
}

int	get_prev_type(t_dlist *lst)
{
	t_dlist	*aux;	
	int		tkn;

	aux = lst;
	aux = aux->prev;
	if (!aux)
		return (-1);
	tkn = ((t_token_data *)aux->content)->token;
	return (tkn);
}

static t_dlist	*handle_executor(t_gdata *gdata, t_dlist *aux, int *end)
{
	int	next_type;
	int	prev_type;
	char	*cmd;

	next_type = get_next_type(aux);
	prev_type = get_prev_type(aux);
	cmd = ft_strtrim((((t_token_data *)aux->content)->str), " ");
	cmd = ft_strtrim(cmd, " ");
	if (next_type == 0)	//pipe
	{
		printf("TIPO1\n");
		printf("MANDO CMD: %s\n", cmd);
		printf("FD: %d\n", gdata->fd[0]);
		handle_cmd1(gdata->fd[0], end, cmd, gdata->envp);
	}
	else if (next_type == 2 || next_type == 4 || prev_type == 2)	//redirección
	{
		printf("TIPO2\n");
		aux = do_red_or_app(aux, gdata);
		if (gdata->fd[1] == -1)
			return (0);
		if (prev_type != 3)
			handle_cmd2(gdata->fd[1], end, cmd, gdata->envp);
	}
	//else if (next_type == -1)		//un cmd
	else
	{
		printf("TIPO3\n");
		handle_cmd3(0, end, cmd, gdata->envp);
		aux = aux->next;
	}
	gdata->commands--;
	return (aux);
}

int		next_is_heredoc(t_dlist *aux)
{
	int	tkn;
	int	it_is;

	aux = aux->next;
	tkn = ((t_token_data *)aux->content)->token;
	it_is = 0;
	if (tkn == 3)
		it_is = 1;
	return (it_is);
}

t_dlist	*do_here_cmd(t_dlist *lst, t_gdata *gdata, int *end)
{
	t_dlist	*aux;
	char	*cmd;

	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	printf("CMD: %s\n", cmd);
	aux = lst;
	lst	= lst->next;
	lst = do_heredoc(lst);
	handle_cmd3(0, end, cmd, gdata->envp);
	return (lst);
}

void	executor(t_gdata *gdata)
{
	t_dlist	*aux;
	int		end[2];

	aux = gdata->cmds_list;
	pipe(end);
	while (aux && gdata->commands > 0)
	{
		char* cmd = ft_strtrim((((t_token_data *)aux->content)->str), " ");
		int tkn = ((t_token_data *)aux->content)->token;
		printf("CMD0: %s\n", cmd);
		printf("TKN0: %d\n", tkn);
		printf("NCOM1: %d\n", gdata->commands);
		if (next_is_heredoc(aux))
			aux = do_here_cmd(aux, gdata, end);
		else if (is_heredoc(aux))
			aux = do_heredoc(aux);
		else if (is_infile(aux))
			aux = do_infile(aux, gdata);
		else
			aux = handle_executor(gdata, aux, end);
		printf("NCOM2: %d\n", gdata->commands);
	}
}
