/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:37 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/20 16:46:30 by goliano-         ###   ########.fr       */
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

//TODO -> funcion que imprima y retorne error

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

//TODO-> diferenciar error de no existe a no acceder y comprobar codigos
void	go_path(t_gdata *data, char **cmd)
{
	char	*tmp;
	DIR		*dir;
	int		i;

	i = 0;
	dir = opendir(cmd[1]);
	if (!dir)
	{
		perror("minishell");
		return ;
	}
	closedir(dir);
	if (data->env->old_pwd)
		free(data->env->old_pwd);
	data->env->old_pwd = ft_strdup(data->env->pwd);
	chdir(cmd[1]);
	tmp = safe_getcwd(data->env->pwd, &i);
	if (data->env->pwd)
		free(data->env->pwd);
	data->env->pwd = ft_strdup(tmp);
	if (!i)
		free (tmp);
}

/*void	init_cd(t_gdata *gdata)
{
	if (gdata->env->home)
		free(gdata->env->home);
	if (gdata->env->pwd && *gdata->env->pwd)
		free(gdata->env->pwd);
	gdata->env->home = ft_dup_var(&gdata->env->env_lst, "HOME");
	gdata->env->pwd = ft_dup_var(&gdata->env->env_lst, "PWD");
}*/

int	ft_cd(t_gdata *data, char **cmd)
{
	char	*aux_pwd;

	init_cd(data);
	if (ft_strlen(cmd[1]) > 255)
	{
		ft_free_matrix(cmd);
		return (put_cd_error(cmd[1], FILENAME, cmd));
	}
	if ((!ft_strcmp(cmd[1], "~") || !cmd[1]))
		go_home(data, cmd);
	else
		go_path(data, cmd);
	aux_pwd = ft_strdup(data->env->pwd);
	check_var_replace(&data->env->env_lst, "PWD", data->env->pwd);
	if (!data->env->pwd)
	{
		data->env->pwd = ft_strdup(aux_pwd);
	}
	if (!check_var_replace(&data->env->env_lst, "OLDPWD", data->env->old_pwd))
		ft_add_var(&data->env->env_lst, "OLDPWD", data->env->old_pwd);
	ft_free_matrix(cmd);
	free(aux_pwd);
	return (EXIT_SUCCESS);
}
