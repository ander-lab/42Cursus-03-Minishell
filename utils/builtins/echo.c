/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:19:57 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/03 16:20:04 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_cmd_proc(char **cmd, int red, t_gdata *gdata)
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
			ft_putnbr_fd(s_glob.proc, fd);
			write(fd, "\n", 1);
			s_glob.proc = 0;
			return (1);
		}
		x++;
	}
	s_glob.proc = 0;
	return (0);
}
