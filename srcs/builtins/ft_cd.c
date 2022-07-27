/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:37 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/26 11:50:54 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO -> MAX FILE NAME ES 255 en bash

int	chdir_env(t_gdata *data)
{
	chdir(path);
	getcwd(pwd, 255);
	return (0);
}

int		max_name(char *file)
{
	ft_putstr_fd(file, 1);
	ft_putstr_fd(": File name too long", 1);
	return (0);
}

void	go_home(t_gdata *data, char **args, int count)
{
	if (count != 1 || (count <= 2 && !ft_strchr(args[1], '~')))
		return ;
}

int	ft_cd(t_gdata *data, char **args)
{
	char			*tmp;
	t_matrix_data 	matrix_data;

	data = ft_matrix_data(args);
	go_home(home, pwd, matrix_data.line_count, args);
	if (ft_strlen(args[1]) > 255)
		return (max_name(args[1]));
	return (EXIT_SUCCESS);
}
