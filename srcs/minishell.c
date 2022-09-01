/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:33:37 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/31 17:43:29 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*void	free_t_env(t_list *lst)
{
	char	*key;
	char	*value;

	while (lst)
	{
		key = ((t_env_line *)(lst)->content)->key;
		value = ((t_env_line *)(lst)->content)->value;
		free(key);
		free(value);
		lst = lst->next;
	}
}*/

void	free_gdata(t_gdata *gdata)
{
	ft_free_matrix(gdata->env->envp);
	//ft_free_matrix(gdata->cmds);
	free_t_lst(gdata->env->env_lst);
	//free_t_env(gdata->env->env_lst);
	free(gdata->prompt);
	free(gdata->env);
	//free_t_cmds(gdata->cmds_lst);
	//free(gdata->heredoc);
}

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

/*void leaks()
{
	system("leaks -q minishell");
}*/

int	main(int argc, char **argv, char **envp)
{
	char		*inp;
	extern char	**environ;
	t_gdata		gdata;

	(void)argc;
	(void)argv;
	init_prompt(&gdata, environ);
	init_env(&gdata, envp);
	//atexit(leaks);
	g_glob.proc = 0;
	//free_gdata(&gdata);
	while (42)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_sigint);
		inp = readline(gdata.prompt);
		if (!inp)
		{
			free_gdata(&gdata);
			return (1);
		}
		if (inp[0])
			add_history(inp);
		lexer(inp, &gdata);
	}
	printf("LLEGO\n");
	free_gdata(&gdata);
	//free(gdata.prompt);
	return (0);
}
