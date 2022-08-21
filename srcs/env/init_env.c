/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:57:09 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/21 17:47:08 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	increase_shlvl(t_list **lst, int shlvl)
{
	t_list	*aux_iter;

	if (!lst || !*lst)
		return ;
	aux_iter = *lst;
	while (aux_iter)
	{
		if (!ft_strcmp((((t_env_line *)(aux_iter)->content)->key), "SHLVL"))
		{
			shlvl = ft_atoi(((t_env_line *)(aux_iter)->content)->value);
			shlvl += 1;
			free((((t_env_line *)(aux_iter)->content)->value));
			((t_env_line *)(aux_iter)->content)->value = ft_itoa(shlvl);
			return ;
		}
		aux_iter = aux_iter->next;
	}
}

char	**build_env(void)
{
	char	**env;

	env = ft_calloc(sizeof(char *), 3);
	env[0] = ft_strjoin_token("PWD", safe_getcwd("not_found"), '=');
	env[1] = ft_strjoin_token("SHLVL", "0", '=');
	env[2] = NULL;
	return (env);
}

void	init_env(t_gdata *data, char **envp)
{
	data->env = ft_calloc(sizeof(t_env), 1);
	if (!*envp)
		data->env->envp = build_env();
	else
		data->env->envp = ft_matrix_dup(envp, ft_matrixlen(envp));
	envp_to_lst(data->env->envp, &data->env->env_lst);
	increase_shlvl(&data->env->env_lst, data->env->shlvl);
	lst_to_envmtrx(data->env->env_lst, data);
}
