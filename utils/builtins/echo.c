/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:19:57 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/24 01:29:19 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_cmd_proc(char **cmd, int red)
{
	int	x;
	int	fd;

	x = 0;
	if (red < 2)
		fd = 1;
	while (cmd[x])
	{
		if (ft_strcmp(cmd[x], "$?") == 0)
		{
			ft_putnbr_fd(g_glob.proc, fd);
			write(fd, "\n", 1);
			g_glob.proc = 0;
			return (1);
		}
		x++;
	}
	g_glob.proc = 0;
	return (0);
}
