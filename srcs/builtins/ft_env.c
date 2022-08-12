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

static int	print_env(char **env, t_gdata *gdata, int red)
{
	int	i;

	i = 0;
	while (env[i])
	{
		print_built_out(env[i], gdata, red);
		print_built_out("\n", gdata, red);
		/*if (ep)
		{
			ft_putstr_fd(env[i], fd[r][WRITE_END]);
			write(fd[r][WRITE_END], "\n", 1);
		}
		else
		{
			ft_putstr_fd(env[i], 1);
			write(1, "\n", 1);
		}*/
		i++;
	}
	return (0);
}

int ft_env(t_gdata *gdata, char **args, int red)
{
	if (args[1] || !gdata->envp)
		return (env_error(args));
	else
	{
		output_type(gdata, red);
		print_env(gdata->envp, gdata, red);
	}
	return (0);
}
