/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:33:37 by goliano-          #+#    #+#             */
/*   Updated: 2022/09/05 10:19:19 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int n)
{
	if (n == 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void leaks()
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char		*inp;
	extern char	**environ;
	t_gdata		gdata;

	(void)argc;
	(void)argv;
	init_prompt(&gdata, environ);
	init_env(&gdata, envp);
	g_glob.proc = 0;
	while (42)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
		inp = readline(gdata.prompt);
		if (!inp)
		{
			free_gdata(&gdata, 0);
			atexit(leaks);
			return (1);
		}
		if (inp[0])
			add_history(inp);
		lexer(inp, &gdata);
	}
	printf("LLEGO\n");
	free_gdata(&gdata, 0);
	return (0);
}
