/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:33:37 by goliano-          #+#    #+#             */
/*   Updated: 2022/02/09 15:24:02 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		inp = readline(g_data.prompt);
		//printf("C: %c\n", inp[0]);
		//return 1;
		if (inp[0])
		{
			//printf("-----DEBUGGER00----\n");
			add_history(inp);
		}
		//lexer(inp);
		printf("INP: %s\n", inp);
	}
	return (0);
}
