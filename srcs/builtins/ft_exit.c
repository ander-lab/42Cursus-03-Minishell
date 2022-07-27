/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:09:15 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/26 20:32:26 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO --> Exit normal return (0)
//TODO --> Exit con código numérico como argumento de exit, returnar ese valor.
//TODO --> Exit con retorno de 255 + imprimir bash: exit: {COMANDO}: numeric argument required
#include "../../includes/minishell.h"

static int ft_exit_with_args(char **cmd, int lines)
{
	if (!ft_iter_str_bool(cmd[1], ft_isdigit))
	{
		ft_putstr_fd("exit: ", 1);
		ft_putstr_fd(cmd[1], 1);
		ft_putstr_fd(": numeric argument require\n", 1);
		//TODO -> Liberar memoria / hacer funcion de exit que libere todo
		exit(255);
	}
	else if (lines > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 1);
		return (1);
	}
	else
		exit (ft_atoi(cmd[1]));
	return (0);
}

int	ft_exit(char **cmd, t_gdata *data)
{
	int				ret;

	ret = 0;
	if (ft_matrixlen(cmd) == 1)
		exit(0);
	else if (ft_matrixlen(cmd) >= 2)
		ft_exit_with_args(cmd, ft_matrixlen(cmd));
	return (ret);
}
