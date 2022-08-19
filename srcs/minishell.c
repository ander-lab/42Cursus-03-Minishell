/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:33:37 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/18 17:42:10 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_sigint(int n)
{
	if (n == 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}


//void	init_env(t_gdata *gdata, char **envp)
//{
//	gdata->env->
//}

int main(int argc, char **argv, char **envp)
{
	char		*inp;
	extern char	**environ;
	t_gdata		gdata;
	
	printf("ARGC: %d\n", argc);
	printf("ARGV[0]: %s\n", argv[0]);
	init_prompt(&gdata, environ);
	init_env(&gdata, envp);
	//TODO -> CHEQUEAR SI ENV EXISTE E INICIALIZAR LAS VARIABLES BASICAS
	s_glob.proc = 0;
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
