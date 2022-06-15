/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:41:24 by ajimenez          #+#    #+#             */
/*   Updated: 2022/06/14 14:02:48 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static _Bool	env_exist(char **cmd, t_env *env)
{
	if (ft_strncmp(cmd[1], const char *s2, size_t n))
}

int ft_export(t_env *env, char **cmd)	
{
	t_matrix_data matrix_data;

	matrix_data = ft_matrix_data(cmd);
	if (matrix_data.line_count == 0)
		ft_putstr_fd("\n", 1);
	else
		//TODO -> funcion que busque y agregue al final dell nodo
		f
}
