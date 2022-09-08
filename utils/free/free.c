/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:43:29 by goliano-          #+#    #+#             */
/*   Updated: 2022/09/08 12:03:29 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void safe_free(void *content)
{
	if (content)
		free(content);
}

void	free_t_lst(t_list *lst)
{
	char	*key;
	char	*value;
	t_list	*aux;

	while (lst)
	{
		key = ((t_env_line *)(lst)->content)->key;
		value = ((t_env_line *)(lst)->content)->value;
		free(key);
		free(value);
		free(lst->content);
		aux = lst;
		lst = lst->next;
		free(aux);
	}
	free(lst);
}

void	free_t_cmds(t_cmds *cmds)
{
	t_cmds	*tmp;

	while (cmds)
	{
		tmp = cmds;
		free(cmds->content);
		cmds = cmds->next;
		free(tmp);
	}
}

void	free_t_dlst(t_dlist *lst)
{
	t_dlist		*aux;

	while (lst)
	{
		aux = lst;
		free(((t_token_data *)(aux)->content)->str);
		free(aux->content);
		lst = lst->next;
		free(aux);
	}
}

void	free_gdata(t_gdata *gdata, int t)
{
	int	x;

	x = 0;
	ft_free_matrix(gdata->env->envp);
	free_t_lst(gdata->env->env_lst);
	free(gdata->prompt);
	//safe_free(gdata->env);
	//free(gdata->env);
	if (t > 0)
	{
		free_t_cmds(gdata->cmds_lst);
		ft_free_matrix(gdata->cmds);
		free_t_dlst(gdata->glob_lst);
		free(gdata->heredoc);
		while (x < gdata->prev_n_pipes - 1)
		{
			free(gdata->fd[x]);
			x++;
		}
		free(gdata->fd);
	}
}
