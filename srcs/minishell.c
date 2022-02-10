/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:33:37 by goliano-          #+#    #+#             */
/*   Updated: 2022/02/09 18:40:20 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void signal_handler(int n)
{
	/* Ctrl + C */
	if (n == SIGINT)
		exit(0);
	/* Ctrl + \ */
	if (n == SIGQUIT)
		exit(0);
}

int main(int argc, char **argv)
{
	char		*inp;
	extern char	**environ;
	t_gdata		g_data;
	
	printf("ARGC: %d\n", argc);
	printf("ARGV[0]: %s\n", argv[0]);
	init_prompt(&g_data, environ);
	//execve("/usr/bin/whoami", cmd, environ);
	//execve("/usr/bin/hostnamectl", cmd, environ);
	while (42)
	{
		signal(SIGQUIT, signal_handler);
		signal(SIGINT, signal_handler);
		inp = readline(g_data.prompt);
		//printf("C: %c\n", inp[0]);
		//return 1;
		if (!inp)
			return (1);
		if (inp[0])
			add_history(inp);
		//lexer(inp);
		printf("INP: %s\n", inp);
	}
	return (0);
}
