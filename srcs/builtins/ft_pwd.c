/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:51:36 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/10 15:54:48 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

int	ft_pwd(t_gdata *gdata, int red)
{
	char	*pwd;
	char	*old;

	output_type(gdata, red);
	pwd = getcwd(NULL, 0);
	print_built_out(pwd, gdata, red);
	print_built_out("\n", gdata, red);
	if (!getcwd(NULL, FILENAME_MAX))
		pwd = ft_strdup(gdata->env->pwd);
	else
		pwd = getcwd(NULL, FILENAME_MAX);
	free (pwd);
	return (EXIT_SUCCESS);
}
