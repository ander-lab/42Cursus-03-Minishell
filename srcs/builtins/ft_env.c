/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:54:10 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/20 13:41:14 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_error(char **args)
{
	ft_putstr_fd("env: ", 1);
	ft_putstr_fd(args[1], 1);
	ft_putstr_fd(": No such file or directory\n", 1);
	ft_free_matrix(args);
	return (127);
}

static int	print_env(char **env, t_gdata *gdata, int red)
{
	int	i;

	i = 0;
	while (env[i])
	{
		print_built_out(env[i], gdata, red);
		print_built_out("\n", gdata, red);
		i++;
	}
	return (0);
}

int	ft_env(char **args, t_gdata *data, int red, int exp)
{
	if (args[1] || !data->env->envp)
		return (env_error(args));
	else
	{
		output_type(data, red);
		print_env(data->env->envp, data, red);
	}
	if (exp == 1)
		ft_free_matrix(args);
	return (0);
}
