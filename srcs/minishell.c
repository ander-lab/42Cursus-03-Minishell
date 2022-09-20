/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:33:37 by goliano-          #+#    #+#             */
/*   Updated: 2022/09/20 12:02:31 by goliano-         ###   ########.fr       */
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

void	signal_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}

static void	init_data(t_gdata *gdata, char **envp, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	g_glob.proc = 0;
	init_env(gdata, envp);
	gdata->cmds_lst = NULL;
	gdata->cmds = NULL;
	gdata->glob_lst = NULL;
	gdata->fd = NULL;
	gdata->heredoc = NULL;
	gdata->n_pipes = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char		*inp;
	extern char	**environ;
	t_gdata		gdata;
	int			i;

	init_prompt(&gdata, environ);
	init_data(&gdata, envp, argc, argv);
	i = 0;
	while (42)
	{
		signal_handler();
		inp = readline(gdata.prompt);
		if (!inp)
		{
			free_gdata(&gdata, i);
			return (1);
		}
		if (inp[0])
			add_history(inp);
		lexer(inp, &gdata, i);
		i++;
		free(inp);
	}
	free_gdata(&gdata, 0);
	return (0);
}
