/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:37 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/20 14:18:20 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h>

#define PERMISION 0
#define FILENAME  1
#define HOME      2

int	put_cd_error(char *arg, int code, char **cmd)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	if (code == 0)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (code == 1)
	{
		ft_putstr_fd(": File name too long\n", 1);
		ft_free_matrix(cmd);
	}
	else if (code == 2)
		ft_putstr_fd("HOME not set\n", 2);
	else if (code == 3)
		ft_putstr_fd(": No such file or directory\n", 2);
	return (0);
}

void	go_home(t_gdata *data, char **cmd)
{
	char	*tmp;

	if (!data->env->home)
	{
		put_cd_error("", HOME, cmd);
		return ;
	}
	tmp = ft_strdup(data->env->pwd);
	if (data->env->old_pwd)
		free(data->env->old_pwd);
	data->env->old_pwd = ft_strdup(tmp);
	free(data->env->pwd);
	data->env->pwd = ft_strdup(data->env->home);
	chdir(data->env->pwd);
	free(tmp);
}

int	go_path(t_gdata *data, char **cmd)
{
	char	*tmp;
	DIR		*dir;

	dir = opendir(cmd[1]);
	if (!dir)
	{
		perror("minishell");
		return (0);
	}
	closedir(dir);
	if (data->env->old_pwd)
		free(data->env->old_pwd);
	data->env->old_pwd = ft_strdup(data->env->pwd);
	chdir(cmd[1]);
	tmp = safe_getcwd(data->env->pwd);
	if (data->env->pwd)
		free(data->env->pwd);
	data->env->pwd = ft_strdup(tmp);
	return (1);
}

void	swap_vars(t_gdata *data)
{
	check_var_replace(&data->env->env_lst, "PWD", data->env->pwd);
	if (!check_var_replace(&data->env->env_lst, "OLDPWD", data->env->old_pwd))
		ft_add_var(&data->env->env_lst, "OLDPWD", data->env->old_pwd);
}

int	ft_cd(t_gdata *data, char **cmd)
{
	int	i;

	init_cd(data);
	if (ft_strlen(cmd[1]) > 255)
	{
		ft_free_matrix(cmd);
		return (put_cd_error(cmd[1], FILENAME, cmd));
	}
	if ((!ft_strcmp(cmd[1], "~") || !cmd[1]))
		go_home(data, cmd);
	else
		i = go_path(data, cmd);
	if (i == 1)
		swap_vars(data);
	ft_free_matrix(cmd);
	return (EXIT_SUCCESS);
}
