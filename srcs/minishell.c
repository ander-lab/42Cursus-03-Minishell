/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:33:37 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/30 16:14:13 by goliano-         ###   ########.fr       */
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

void	free_gdata(t_gdata *gdata)
{
	ft_free_matrix(gdata->env->envp);
	free_t_lst(gdata->env->env_lst);
	//free_t_env_line(gdata->env->env_lst);
}

int	main(int argc, char **argv, char **envp)
{
	//char		*inp;
	extern char	**environ;
	t_gdata		gdata;

	if (argc < 0 && !argv)
		return (0);
	init_prompt(&gdata, environ);
	init_env(&gdata, envp);
	g_glob.proc = 0;
	free_gdata(&gdata);
	atexit(leaks);
	/*while (42)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
		inp = readline(gdata.prompt);
		if (!inp)
			return (1);
		if (inp[0])
			add_history(inp);
		lexer(inp, &gdata);
	}
	free(gdata.prompt);
	return (0);*/
}
