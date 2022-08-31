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

void	free_double_p_char(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	free_t_lst(t_list *lst)
{
	while (lst)
	{
		free(lst->content);
		lst = lst->next;
	}
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

void	free_t_env(t_env *env)
{
	ft_free_matrix(env->envp);
	//free(env->home);
	//free(env->pwd);
	//free(env->old_pwd);
	//while (lst)
//	{
//		lst = lst->next;
//	}

}
