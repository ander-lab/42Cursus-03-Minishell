/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 20:21:40 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/20 20:30:03 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_gdata_handle(t_gdata *gdata)
{
	gdata->r = -1;
	gdata->fd = init_fds(gdata);
}

static void	exit_error_fork(void)
{
	perror("Fork: ");
	exit(EXIT_FAILURE);
}

void	handle_cmd(t_gdata *gdata, t_cmds *cmds)
{
	int		*pids;
	int		built;

	init_gdata_handle(gdata);
	pids = ft_calloc(sizeof(int), gdata->n_pipes + 1);
	while (++(gdata->r) < gdata->n_pipes + 1)
	{
		built = check_builtin(gdata, cmds);
		child_signal_handler(pids[gdata->r]);
		if (!built)
		{
			pids[gdata->r] = fork();
			if (pids[gdata->r] == -1)
				exit_error_fork();
			if (pids[gdata->r] == 0)
			{
				do_child(cmds, gdata->r, gdata);
				handle_here_exec(cmds, gdata, gdata->r);
			}
		}
		cmds = cmds->next;
	}
	close_fds(gdata, pids);
}
