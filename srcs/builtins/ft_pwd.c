/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:51:36 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/17 12:59:15 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

int	ft_pwd(t_gdata *gdata, int red)
{
	char	*pwd;
	char	*cwd;

	output_type(gdata, red);
	cwd = getcwd(NULL, FILENAME_MAX);
	if (!cwd)
		pwd = ft_strdup(gdata->env->pwd);
	else
		pwd = getcwd(NULL, FILENAME_MAX);
	print_built_out(pwd, gdata, red);
	print_built_out("\n", gdata, red);
	free(cwd);
	free (pwd);
	return (EXIT_SUCCESS);
}
