/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:44:28 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/27 16:22:46 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_echo(int red, char **s, int i)
{
	if (red > 2)
		write(red, s[i], ft_strlen(s[i]));
	else
		write(1, s[i], ft_strlen(s[i]));
	if (s[i + 1])
	{
		if (red > 2)
			write(red, " ", 1);
		else
			write(STDOUT_FILENO, " ", 1);
	}
}

static void	ft_put_echo(char **s, int i, int red)
{
	while (s[i])
	{	
		write_echo(red, s, i);
		i++;
	}
}

static int	check_flag(char *str)
{
	int	i;

	i = 2;
	if (!str || (str[0] != '-' && str[1] == 'n'))
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_print_no_nl(char **s, int red)
{
	int	i;

	i = 2;
	while (s[i] && check_flag(s[i]) == 1)
		i++;
	if (!s[i])
		return (127);
	ft_put_echo(s, i, red);
	return (EXIT_SUCCESS);
}

int	ft_echo(char **cmd, int red)
{
	if (!cmd[1])
	{
		if (red > 2)
			write(red, "\n", 1);
		else
			write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	if (!check_flag(cmd[1]))
	{
		ft_put_echo(cmd, 1, red);
		if (red > 2)
			write(red, "\n", 1);
		else
			write(STDOUT_FILENO, "\n", 1);
	}
	else
		ft_print_no_nl(cmd, red);
	return (EXIT_SUCCESS);
}
