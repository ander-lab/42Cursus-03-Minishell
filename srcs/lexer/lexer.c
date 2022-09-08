/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:58:58 by goliano-          #+#    #+#             */
/*   Updated: 2022/09/08 12:39:24 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_gdata(char *s, t_gdata *gdata)
{
	gdata->n_commands = get_n_commands(s);
	gdata->aux_n_commands = gdata->n_commands;
	gdata->n_tokens = get_n_tokens(s);
	gdata->handle_next = 0;
	gdata->commands = command_count(s);
	gdata->inf_err = 0;
	gdata->err = 0;
	gdata->fd_pipe = -1;
	gdata->n_pipes = 0;
	gdata->prev_n_pipes = 0;
}

void	lexer(char *s, t_gdata *gdata, int i)
{
	init_gdata(s, gdata);
	s = ft_strtrim(s, " ");
	if (ft_strlen(s) == 0 || exists_error(s, gdata))
	{
		free(s);
		return ;
	}
	handle_input(s, gdata, i);
	if (gdata->err)
	{
		free(s);
		return ;
	}
	init_tokens(s, gdata, i);
	free(s);
	parser(gdata);
	if (gdata->err)
		return ;
	executor(gdata, i);
}
