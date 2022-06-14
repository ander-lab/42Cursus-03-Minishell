/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:33:37 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/14 16:16:18 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* SIGINT CTRL + C == 2
 *
 *
 *
 */

void handle_sigint(int n)
{
	if (n == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

int main(int argc, char **argv)
{
	char		*inp;
	extern char	**environ;
	t_gdata		gdata;
	
	printf("ARGC: %d\n", argc);
	printf("ARGV[0]: %s\n", argv[0]);
	init_prompt(&gdata, environ);
	//printf("VER: %d\n", rl_readline_version);
	//execve("/usr/bin/whoami", cmd, environ);
	//execve("/usr/bin/hostnamectl", cmd, environ);
	while (42)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
		inp = readline(gdata.prompt);
		//printf("C: %c\n", inp[0]);
		//return 1;
		if (!inp)
			return (1);
		if (inp[0])
			add_history(inp);
		lexer(inp, &gdata);
		//printf("INP: %s\n", inp);
	}
	free(gdata.prompt);
	return (0);
}
