/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:54:10 by ajimenez          #+#    #+#             */
/*   Updated: 2022/05/26 15:11:17 by goliano-         ###   ########.fr       */
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

int ft_env(char **env, char **args)
{
	if (args[1] || !env)
		return (env_error(args));
	else
		print_env(env);
	return (0);
}
