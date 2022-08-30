/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:19:37 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/30 11:44:25 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_access(char *cmd, char **mycmdargs, char **envp, int t)
{
	int	r;

	r = 0;
	if (t)
	{
		if (access(cmd, X_OK) > -1)
		{
			execve(cmd, mycmdargs, envp);
			r = 1;
		}
	}
	else
	{
		if (access(mycmdargs[0], X_OK) > -1)
		{
			execve(mycmdargs[0], mycmdargs, envp);
			r = 1;
		}
	}
	return (r);
}

static int	path_index(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (i);
}

static char	**handle_more(char **envp)
{
	int		i;
	char	*path;
	char	**all_paths;

	i = 0;
	i = path_index(envp);
	path = ft_strtrim(envp[i], "PATH=");
	if (!path)
		return (0);
	all_paths = ft_split(path, ':');
	return (all_paths);
}

static char	*handle_path_chequer(char *cmd)
{
	if (!cmd)
		exit(127);
	if (need_cmd_slash(cmd))
		cmd = cmd_add_slash(cmd);
	return (cmd);
}

int	handle_path(char *cmd, char **envp)
{
	int		i;
	char	**all_paths;
	char	**mycmdargs;
	char	*cmd_one;

	cmd = handle_path_chequer(cmd);
	all_paths = handle_more(envp);
	mycmdargs = smart_split(cmd, ' ');
	i = -1;
	while (mycmdargs[++i])
		mycmdargs[i] = ft_strtrim(mycmdargs[i], " ");
	if (check_access(cmd, mycmdargs, envp, 0))
		exit(EXIT_SUCCESS);
	i = -1;
	while (all_paths[++i])
	{
		cmd_one = ft_strjoin(all_paths[i], mycmdargs[0]);
		if (check_access(cmd_one, mycmdargs, envp, 1))
			exit(EXIT_SUCCESS);
		free(cmd_one);
	}
	perror("");
	exit(127);
}
