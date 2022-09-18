/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:19:37 by goliano-          #+#    #+#             */
/*   Updated: 2022/09/12 16:03:51 by goliano-         ###   ########.fr       */
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
	free(path);
	return (all_paths);
}

static void	handle_path2(char **all_paths, char **mycmdargs, char **envp)
{
	char	*cmd_one;
	int		i;

	i = -1;
	if (!all_paths)
	{
		//perror("1");
		printf("command not found\n");
		exit(127);
	}
	while (all_paths[++i])
	{
		cmd_one = ft_strjoin(all_paths[i], mycmdargs[0]);
		if (check_access(cmd_one, mycmdargs, envp, 1))
		{
			ft_free_matrix(mycmdargs);
			exit(EXIT_SUCCESS);
		}
		free(cmd_one);
	}
	ft_free_matrix(mycmdargs);
	//perror("2");
	printf("command not found\n");
}

int	handle_path(char *cmd, char **envp)
{
	int		i;
	char	**all_paths;
	char	**mycmdargs;
	char	*tmp;

	if (!cmd)
		exit(127);
	if (need_cmd_slash(cmd))
		cmd = cmd_add_slash(cmd);
	all_paths = handle_more(envp);
	mycmdargs = smart_split(cmd, ' ');
	i = -1;
	while (mycmdargs[++i])
	{
		tmp = ft_strtrim(mycmdargs[i], " ");
		free(mycmdargs[i]);
		mycmdargs[i] = tmp;
	}
	if (check_access(cmd, mycmdargs, envp, 0))
	{
		ft_free_matrix(mycmdargs);
		exit(EXIT_SUCCESS);
	}
	handle_path2(all_paths, mycmdargs, envp);
	exit(127);
}
