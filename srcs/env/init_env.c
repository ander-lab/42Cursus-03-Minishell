/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:57:09 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/12 12:09:42 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	increase_shlvl(t_list **lst)
{
	t_list	*aux_iter;
	int	shlvl = 0;

	int i = 0;
	if (!lst || !*lst)
		return ;
	aux_iter = *lst;
	while (aux_iter)
	{
		//printf("%s \n %s\n", (((t_env_line *)(aux_iter)->content)->key), key);
		//i++;
		if (!ft_strcmp((((t_env_line *)(aux_iter)->content)->key), "SHLVL"))
		{
			shlvl = ft_atoi((((t_env_line *)(aux_iter)->content)->value));
			shlvl += 1;
			free((((t_env_line *)(aux_iter)->content)->value));
			((t_env_line *)(aux_iter)->content)->value = ft_itoa(shlvl);
			return ;
		}
		aux_iter = aux_iter->next;
	}
	//printf("NO EXISTE\n");
}

char	**build_env(void)
{
	char	**env;

	env = ft_calloc(sizeof(char *), 3);
	env[0] = ft_strjoin_token("PWD", safe_getcwd("not_found"), '=');
	env[1] = ft_strjoin_token("SHLVL", "1", '=');
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
	increase_shlvl(&data->env->env_lst);
}