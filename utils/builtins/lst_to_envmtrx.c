/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_envmtrx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 20:46:33 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/30 16:14:08 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lst_to_envmtrx(t_list *lst_env, t_gdata *gdata)
{
	int	i;

	i = 0;
	ft_free_matrix(gdata->env->envp);
	gdata->env->envp = malloc((ft_lstsize(lst_env) + 1) * (sizeof(char *)));
	while (lst_env)
	{
		gdata->env->envp[i]
			= ft_strjoin_token(((t_env_line *)lst_env->content)->key,
				((t_env_line *)lst_env->content)->value,
				'=');
		lst_env = lst_env->next;
		i++;
	}
	gdata->env->envp[i] = NULL;
}
