/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:41:24 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/09 14:43:20 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>


int	check_var_replace(t_list **lst, char *key, char *value)
{
	t_list	*aux_iter;

	int i = 0;
	if (!lst || !*lst)
		return (0);
	aux_iter = *lst;
	while (aux_iter)
	{
		//printf("%s \n %s\n", (((t_env_line *)(aux_iter)->content)->key), key);
		//i++;
		if (!ft_strcmp((((t_env_line *)(aux_iter)->content)->key), key))
		{
			free((((t_env_line *)(aux_iter)->content)->value));
			((t_env_line *)(aux_iter)->content)->value = ft_strdup(value);
			return (1);
		}
		aux_iter = aux_iter->next;
	}
	//printf("NO EXISTE\n");
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
	//ft_printkey(*lst);
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


int	ft_export(t_list **env, char **cmd)
{
	char	**var;


//	printf("EXISTEEEE\n\n");
	if (cmd[1])
		var = split_once(cmd[1]); 
	if (!cmd[1])
	{
		//printf("==SALE==");
		ft_putchar_fd('\n', 1);
	}
	else if (!check_var_replace(env, var[0], var[1]))
	{
	//	printf("ta entrando\n");
	//	printf("--------------------DEBUUUUUUUUUUUUUUUUUUUG--------------------------\n");
		ft_add_var(env, var[0], var[1]);
	}
//	printf("------------------------------------------------------------------------------");
//	ft_printkey(*env);
//	printf("------------------------------------------------------------------------------");
//	printf("\n");
	return (0);
}
