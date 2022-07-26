/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:44:28 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/26 11:58:53 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_put_echo(char **s, int i)
{
	while (s[i])
	{
		write(1, s[i], ft_strlen(s[i]));
		if (s[i + 1])
			write(STDOUT_FILENO, " ", 1);
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

static int ft_print_no_nl(char **s)
{
	int	i;

	i = 2;
	while (s[i] && check_flag(s[i]) == 1)
		i++;
	if (!s[i])
		return (EXIT_FAILURE);
	ft_put_echo(s, i);
	return (EXIT_SUCCESS);
}

int	ft_echo(char **cmd)
{
	if (!cmd[1])
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	if (!check_flag(cmd[1]))
	{
		ft_put_echo(cmd, 1);
		printf("\n");
	}
	else
		ft_print_no_nl(cmd);
	return (EXIT_SUCCESS);
}
