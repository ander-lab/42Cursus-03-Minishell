/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:45:42 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/12 14:52:50 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_new_line(char *str)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * ft_strlen(str));
	if (!word)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	free(str);
	return (word);
}

char	*cmd_output(int fd)
{
	char	*out;

	out = get_next_line(fd);
	get_next_line(fd);
	out = remove_new_line(out);
	close(fd);
	return (out);
}

char	*exec_command(char *cmd, char **envp)
{
	int		end[2];
	pid_t	p;
	char	**sp;

	pipe(end);
	p = fork();
	if (p < 0)
		return (0);
	if (p == 0)
	{
		close(end[0]);
		sp = ft_split(cmd, ' ');
		dup2(end[1], STDOUT_FILENO);
		close(end[1]);
		if (!access(cmd, X_OK))
			execve(cmd, sp, envp);
		exit(1);
	}
	close(end[1]);
	waitpid(p, NULL, 0);
	return (cmd_output(end[0]));
}

void	init_prompt(t_gdata *g_data, char **envp)
{
	char	*username;
	char	*hostname;

	username = exec_command("/usr/bin/whoami", envp);
	username = add_at_sign(username);
	hostname = exec_command("/bin/hostname", envp);
	hostname = pretty_hostname(hostname);
	g_data->prompt = ft_strjoin(username, hostname);
	free(username);
	free(hostname);
}
