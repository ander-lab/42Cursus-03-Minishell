/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:42:25 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/08 11:30:59 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmds	*fill_cmds(char *cmd, int ind, int red, int here)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (0);
	cmds->content = cmd;
	cmds->ind = ind;
	cmds->red = red;
	cmds->here = here;
	cmds->exp = 0;
	cmds->next = NULL;
	return (cmds);
}

//TODO -> NORMINETTE VAR
void ft_printdlst(t_dlist *token_lst)
{
	while (token_lst)
	{
		printf("token  %i char * %s\n", ((t_token_data *)token_lst->content)->token,
			((t_token_data *)token_lst->content)->str);
		token_lst = token_lst->next;
	}
}

void	init_cmds_lst(t_gdata *gdata)
{
	t_cmds	*cmds;
	t_dlist	*glob_lst;

	cmds = NULL;
	glob_lst = gdata->glob_lst;
	while (glob_lst)
	{
		ft_dlstadd_back2(&cmds, fill_cmds(get_cmd(glob_lst), \
				get_ind(glob_lst), get_red(glob_lst), \
				need_exec_here(glob_lst)));
		glob_lst = iter_to_pipe(glob_lst);
	}
	gdata->cmds_lst = cmds;
}
