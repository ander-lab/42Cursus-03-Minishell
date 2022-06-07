/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:17:54 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/07 11:40:48 by goliano-         ###   ########.fr       */
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

/*static t_dlist	*handle_executor(t_gdata *gdata, t_dlist *aux, int *end)
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
}*/

static void	handle_here(t_dlist *lst, t_gdata *gdata)
{
	int	tkn;

	while (exists_heredoc(lst))
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
			do_heredoc(lst, gdata);
		lst = lst->next;
	}
}

void	handle_infile(t_dlist *lst, t_gdata *gdata)
{
	int	tkn;

	while (lst && !gdata->err)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 1)
			do_infile(lst, gdata);
		lst = lst->next;
	}
}

void	executor(t_gdata *gdata)
{
	t_dlist	*lst;
	int		end[2];
	//int	tkn;

	lst = gdata->cmds_list;
	pipe(end);
	handle_here(lst, gdata);
	handle_infile(lst, gdata);
	if (gdata->err)
		return ;
	/*while (lst && gdata->commands > 0)
	{
		char* cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
		tkn = ((t_token_data *)lst->content)->token;
		printf("CMD0: %s\n", cmd);
		printf("TKN0: %d\n", tkn);
		if (is_infile(lst))
			lst = do_infile(lst, gdata);
		else
			lst = handle_executor(gdata, lst, end);
	}*/
}
