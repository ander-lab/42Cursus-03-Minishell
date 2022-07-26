/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:41:24 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/26 11:46:05 by ajimenez         ###   ########.fr       */
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
	printf("NO EXISTE\n");
	return (0);
}

void	ft_add_var(t_list **lst, char *key, char *value)
{
	t_env_line *env_struct;

	env_struct = ft_calloc(sizeof(t_env_line), 1);
	if (!env_struct)
		return ;
	env_struct->key = ft_strdup(key);
	env_struct->value = ft_strdup(value);
	ft_lstadd_back(lst, ft_lstnew_struct(env_struct, sizeof(t_env_line)));
	free(env_struct);
}
//Mismo funcionamiento que unset pero en vez de eliminar el nodo entero y relink, liberar el value.
//En caso de no existir, lstaddback
//Chequear bien la gestión del null
//
static	char	**split_once(char *s)
{
	char **split;

	split = ft_calloc(sizeof(char *), 3);
	split[0] = ft_strdup(ft_split(s, '=')[0]);
	split[1] = ft_strdup(ft_strchr(s, '=') + 1);
	split[2] = NULL;
	return (split);
}
//
int	ft_export(t_list **env, char **cmd)
{
	char	**var;


	//hacer un split modificado con el tema "=" . Debe de hacer un split solamente del primer espacio que encuentre,
	//en caso de no encontrar ninguno meter un null dentro del string content.
	//var = ft_split(cmd[1], '=');
	var = split_once(cmd[1]);
	if (ft_matrixlen(cmd) == 1)
	{
		ft_putchar_fd('\n', 1);
	}
	if (!check_var_replace(env, var[0], var[1]))
	{
		ft_add_var(env, var[0], var[1]);
	}
	return (0);
}
