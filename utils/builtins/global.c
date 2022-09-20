/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:25:47 by goliano-          #+#    #+#             */
/*   Updated: 2022/09/12 16:33:30 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	output_type(t_gdata *gdata, int red)
{
	gdata->type = 0;
	if (red > 2)
		gdata->type = 1;
	else if (gdata->r < gdata->n_pipes)
		gdata->type = 2;
}

void	print_built_out(char *out, t_gdata *gdata, int red)
{
	if (gdata->type == 0)
		write(STDOUT_FILENO, out, ft_strlen(out));
	else if (gdata->type == 1)
		write(red, out, ft_strlen(out));
	else
		write(gdata->fd[gdata->r][WRITE_END], out, ft_strlen(out));
}
