/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:44:28 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/21 16:41:53 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_put_echo(char **s, int i, t_gdata *gdata, int red)
{
	while (s[i])
	{	
		print_built_out(s[i], gdata, red);
		if (s[i + 1])
			print_built_out(" ", gdata, red);
		i++;
	}
}

static int	check_flag(char *str)
{
	int	i;

	i = 2;
	if (!str || (str[0] != '-' && str[1] != 'n'))
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_print_no_nl(char **s, int red, t_gdata *gdata)
{
	int	i;

	i = 2;
	while (s[i] && check_flag(s[i]) == 1)
		i++;
	if (!s[i])
		return (127);
	ft_put_echo(s, i, gdata, red);
	return (EXIT_SUCCESS);
}

int	ft_echo(char **cmd, t_gdata *gdata, int red)
{
	if (print_cmd_proc(cmd, red))
		return (EXIT_SUCCESS);
	output_type(gdata, red);
	if (!cmd[1])
	{
		print_built_out("\n", gdata, red);
		return (EXIT_SUCCESS);
	}
	if (!check_flag(cmd[1]))
	{
		ft_put_echo(cmd, 1, gdata, red);
		print_built_out("\n", gdata, red);
	}
	else
		ft_print_no_nl(cmd, red, gdata);
	return (EXIT_SUCCESS);
}
