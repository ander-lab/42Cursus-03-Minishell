/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:45:42 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/08 10:47:12 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*exec_command(char *cmd, char **envp)
{
	int	end[2];
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
	char *out = malloc(sizeof(char) * 4096);
	out = get_next_line(end[0]);
	out = remove_new_line(out);
	close(end[0]);
	return (out);
}

char	*add_at_sign(char *str)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * ft_strlen(str + 1));
	if (!word)
		return (0);
	i = 0;
	while (str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '@';
	word[i + 1] = '\0';
	free(str);
	return (word);
}

char *pretty_hostname(char *str)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * ft_strlen(str + 3));
	if (!word)
		return (0);
	while(str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = ':';
	word[i + 1] = ' ';
	word[i + 2] = '\0';
	free(str);
	return (word);
}

void	init_prompt(t_gdata *g_data, char **envp)
{
	char	*username;
	char	*hostname;

	g_data->envp = envp;
	username = exec_command("/usr/bin/whoami", envp);
	username = add_at_sign(username);
	hostname = exec_command("/bin/hostname", envp);
	hostname = pretty_hostname(hostname);
	g_data->prompt = ft_strjoin(username, hostname);
}
