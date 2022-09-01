/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:43:29 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/31 17:38:27 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_t_lst(t_list *lst)
{
	char	*key;
	char	*value;
	int	i;
	t_list	*aux;

	i = 0;
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
		i++;
	}
	free(lst);
}

void	free_t_cmds(t_cmds *cmds)
{
	while (cmds)
	{
		free(cmds->content);
		cmds = cmds->next;
	}
	free(cmds);
}
