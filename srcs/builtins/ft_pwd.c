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

int	ft_pwd(t_gdata *data)
{
	char	*pwd;
	char	*old;

	//printf("%p", data->env->env_lst);
	//ft_printkey(data->env->env_lst);
	if (!getcwd(NULL, FILENAME_MAX))
	{
	//	ft_printkey(data->env->env_lst);
	//	printf("\n000000000000000000000000000000000000000000000000000000000000000000000000\n");
	//	return (0);
		pwd = ft_strdup(data->env->pwd);
	}
	else
		pwd = getcwd(NULL, FILENAME_MAX);
//	if (!pwd)
//	{
//		printf("%s\n", old);
//		//pwd = ft_dup_var(&data->env->env_lst, "PWD");
//	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	printf("%s\n", pwd);
	free (pwd);
	return (EXIT_SUCCESS);
}
