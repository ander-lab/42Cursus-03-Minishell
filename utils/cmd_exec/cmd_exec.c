/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:19:37 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/05 16:01:22 by goliano-         ###   ########.fr       */
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

int	handle_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**all_paths;
	char	**mycmdargs;
	char	*cmd_one;

	if (need_cmd_slash(cmd))
		cmd = cmd_add_slash(cmd);
	i = path_index(envp);
	path = ft_strtrim(envp[i], "PATH=");
	all_paths = ft_split(path, ':');
	//if (has_quotes(cmd))
	//	mycmdargs = ft_split_quotes(cmd, ' ');
	//else
		mycmdargs = ft_split(cmd, ' ');
	if (check_access(cmd, mycmdargs, envp, 0))
		exit(EXIT_SUCCESS);
		//return (1);
	i = -1;
	while (all_paths[++i])
	{
		cmd_one = ft_strjoin(all_paths[i], mycmdargs[0]);
		if (check_access(cmd_one, mycmdargs, envp, 1))
			exit(EXIT_SUCCESS);
			//return (1);
		free(cmd_one);
	}
	perror("bash");
	exit(EXIT_FAILURE);
}
