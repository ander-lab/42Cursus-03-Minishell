/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:09:15 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/08 12:30:34 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_exit_with_args(char **cmd, int lines, t_gdata *gdata, int *pids)
{
	int	exit_atoi;

	if (!ft_iter_str_bool(cmd[1], ft_isdigit))
	{
		ft_putstr_fd("exit: ", 1);
		ft_putstr_fd(cmd[1], 1);
		ft_putstr_fd(": numeric argument require\n", 1);
		free_gdata(gdata, 1);
		ft_free_matrix(cmd);
		free(pids);
		exit(255);
	}
	else if (lines > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 1);
		return (1);
	}
	else
	{
		exit_atoi = ft_atoi(cmd[1]);
		free_gdata(gdata, 1);
		ft_free_matrix(cmd);
		free(pids);
		exit(exit_atoi);
	}
	return (0);
}

int	ft_exit(char **cmd, t_gdata *gdata, int *pids)
{
	int				ret;

	ret = 0;
	if (ft_matrixlen(cmd) == 1)
	{
		free_gdata(gdata, 1);
		ft_free_matrix(cmd);
		exit(0);
	}
	else if (ft_matrixlen(cmd) >= 2)
		ft_exit_with_args(cmd, ft_matrixlen(cmd), gdata, pids);
//	free_gdata(gdata, 1);
	ft_free_matrix(cmd);
	return (ret);
}
