/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 09:42:48 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/20 20:31:29 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigquit_child(int n)
{
	if (n == 3)
	{
		write(STDOUT_FILENO, "Quit: 3\n", 8);
		s_glob.proc = 131;
	}
	if (n == 2)
		s_glob.proc = 130;
}

void	child_signal_handler(int pid)
{
	if (pid == 0)
	{
		signal(SIGQUIT, sigquit_child);
		signal(SIGINT, sigquit_child);
	}	
}
