/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:58:58 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/26 13:11:22 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_printdlst(t_dlist *token_lst)
{
	while (token_lst)
	{
		printf("token  %i char * %s\n", ((t_token_data *)token_lst->content)->token,
			((t_token_data *)token_lst->content)->str);
		token_lst = token_lst->next;
	}
}

void	init_gdata(char *s, t_gdata *gdata)
{
	gdata->n_commands = get_n_commands(s);
	gdata->aux_n_commands = gdata->n_commands;
	gdata->n_tokens = get_n_tokens(s);
	gdata->handle_next = 0;
	gdata->commands = command_count(s);
	gdata->inf_err = 0;
	gdata->err = 0;
	gdata->fd_pipe = -1;
}

/*void	free_gdata(t_gdata *gdata)
{
	int	i;

	i = 0;
	while (gdata->cmds[i])
	{
		free(gdata->cmds[i]);
		i++;
	}
}*/

void	lexer(char *s, t_gdata *gdata)
{
	init_gdata(s, gdata);
	s = ft_strtrim(s, " ");
	if (exists_error(s, gdata))
		return ;
	handle_input(s, gdata);
	if (gdata->err)
		return ; //gestion de comillas abiertas lexer
	init_tokens(s, gdata);
	parser(gdata);
	if (gdata->err)
		return ; //gestion de comillas abiertas lexer
	executor(gdata);
}
