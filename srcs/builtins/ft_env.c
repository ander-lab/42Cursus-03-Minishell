/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:54:10 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/27 15:51:25 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_error(char **args)
{
	ft_putstr_fd("env: " , 1);
	ft_putstr_fd(args[1], 1);
	ft_putstr_fd(": No such file or directory\n", 1);
	return (127);
}

static int	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int ft_env(char **args, t_gdata *data)
{
	lst_to_envmtrx(data->env->env_lst, data);
	if (args[1] || !data->env->envp)
		return (env_error(args));
	else
		print_env(data->env->envp);
	return (0);
}
