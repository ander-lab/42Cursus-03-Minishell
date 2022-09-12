/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:41:24 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/08 16:48:07 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	check_var_replace(t_list **lst, char *key, char *value)
{
	t_list	*aux_iter;

	if (!lst || !*lst)
		return (0);
	aux_iter = *lst;
	while (aux_iter)
	{
		if (!ft_strcmp((((t_env_line *)(aux_iter)->content)->key), key))
		{
			free((((t_env_line *)(aux_iter)->content)->value));
			((t_env_line *)(aux_iter)->content)->value = ft_strdup(value);
			return (1);
		}
		aux_iter = aux_iter->next;
	}
	return (0);
}

void	ft_add_var(t_list **lst, char *key, char *value)
{
	t_env_line	*env_struct;

	env_struct = ft_calloc(sizeof(t_env_line), 1);
	if (!env_struct)
		return ;
	env_struct->key = ft_strdup(key);
	env_struct->value = ft_strdup(value);
	ft_lstadd_back(lst, ft_lstnew_struct(env_struct, sizeof(t_env_line)));
	free(env_struct);
}

static	char	**split_once(char *s)
{
	char	**split;
	char	**aux;

	if (!ft_strchr(s, '='))
		return (0);
	aux = ft_split(s, '=');
	split = ft_calloc(sizeof(char *), 3);
	split[0] = ft_strdup(aux[0]);
	split[1] = ft_strdup(ft_strchr(s, '=') + 1);
	split[2] = NULL;
	ft_free_matrix(aux);
	return (split);
}

int	ft_export(t_list **env, char **cmd)
{
	char	**var;

	var = NULL;
	if (cmd[1])
	{
		var = split_once(cmd[1]);
		if (!var || !*var)
		{
			ft_free_matrix(cmd);
			return (0);
		}
	}
	if (!cmd[1])
	{
		ft_putchar_fd('\n', 1);
	}
	else if (!check_var_replace(env, var[0], var[1]))
		ft_add_var(env, var[0], var[1]);
	if (var)
		ft_free_matrix(var);
	ft_free_matrix(cmd);
	return (0);
}
