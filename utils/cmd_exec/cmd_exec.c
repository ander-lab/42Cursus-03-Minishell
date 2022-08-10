/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:19:37 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/09 12:23:49 by goliano-         ###   ########.fr       */
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

static int	*append_free(int *index, int new)
{
	int	ind;
	int	*ret;

	ind = 0;
	while (index[ind] != -1)
		ind++;
	ret = (int *)malloc(sizeof(int) * (ind + 2));
	ret[ind + 1] = -1;
	ret[ind] = new;
	while (--ind >= 0)
		ret[ind] = index[ind];
	free(index);
	return (ret);
}

static int	*index_str(int *index, char *order, char limit)
{
	char	limiter;

	index = append_free(index, index[0]);
	index[1]++;
	limiter = '\0';
	while (order[index[0]] && (order[index[0]] != limit || limiter))
	{
		if (order[index[0]] == '\'' || order[index[0]] == '\"')
		{
			if (!limiter)
				limiter = order[index[0]];
			else if (order[index[0]] == limiter)
				limiter = '\0';
		}
		index[0]++;
	}
	index = append_free(index, index[0]);
	while (order[index[0]] && order[index[0]] == limit)
		index[0]++;
	if (!order[index[0]])
		return (index);
	return (index_str(index, order, limit));
}

char	**smart_split(char *order, char limit)
{
	int		*index;
	char	**ret;
	int		ind;
	int		ind2;

	index = (int *)malloc(sizeof(int) * 3);
	index[0] = 0;
	index[1] = 0;
	index[2] = -1;
	order = ft_strtrim(order, " ");
	index = index_str(index, order, limit);
	ret = (char **)malloc(sizeof(char *) * (index[1] + 1));
	ind = 2;
	ind2 = 0;
	while (index[ind] != -1)
	{
		ret[ind2++] = ft_substr(order, index[ind], \
		(index[ind + 1] - index[ind]));
		ind += 2;
	}
	ret[ind2] = NULL;
	free(order);
	free(index);
	return (ret);
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
	//mycmdargs = ft_split(cmd, ' ');
	//mycmdargs = smart_split(cmd, '\"');
	mycmdargs = smart_split(cmd, ' ');
	int r = 0;
	while (mycmdargs[r])
	{
		mycmdargs[r] = ft_strtrim(mycmdargs[r], " ");
		//write(2, "CMD: \n", 6);
		//write(2, mycmdargs[r], ft_strlen(mycmdargs[r]));
		//write(2, ".\n", 2);
		r++;
	}
	if (check_access(cmd, mycmdargs, envp, 0))
	{
		//write(2, "1\n", 2);
		exit(EXIT_SUCCESS);
	}
		//return (1);
	i = -1;
	while (all_paths[++i])
	{
		//write(2, "2\n", 2);
		cmd_one = ft_strjoin(all_paths[i], mycmdargs[0]);
		//write(2, "CMD_ONE: \n", 10);
		//write(2, cmd_one, ft_strlen(cmd_one));
		//write(2, "\n", 1);
		if (check_access(cmd_one, mycmdargs, envp, 1))
			exit(EXIT_SUCCESS);
			//return (1);
		free(cmd_one);
	}
	perror("");
	exit(127);
}
