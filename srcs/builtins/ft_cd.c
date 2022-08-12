/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:37 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/10 21:09:16 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO -> MAX FILE NAME ES 255 en bash
#define PERMISION 0
#define FILENAME  1
#define HOME      2


int	put_cd_error(char *arg, int code)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	if (code == 0)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (code == 1)
		ft_putstr_fd(": File name too long\n", 1);
	else if (code == 2)
		ft_putstr_fd("HOME not set\n", 2);
	else if (code == 3)
		ft_putstr_fd(": No such file or directory\n", 2);
	return (0);
}

//TODO -> funcion que imprima y retorne error

void	go_home(t_gdata *data, char **args)
{
	char	*tmp;

	if (!data->env->home)
		put_cd_error("", HOME);
		//ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	tmp = ft_strdup(data->env->pwd);
	data->env->old_pwd = ft_strdup(tmp);
	free(data->env->pwd);
	data->env->pwd = ft_strdup(data->env->home);
	chdir(data->env->pwd);
	free(tmp);
}

//TODO-> diferenciar error de no existe a no acceder y comprobar codigos
void	go_path(t_gdata *data, char **cmd)
{
	char *tmp;

	//comprobar si existe la carpeta
	if (open(cmd[1], O_RDONLY) < 0)
	{
		put_cd_error(cmd[1], PERMISION);
	//	ft_putstr_fd("minishell: ", 2);
	//	ft_putstr_fd(cmd[1], 2);
	//	ft_putstr_fd(": Permission denied\n", 2);
		return ;
	}
	data->env->old_pwd = ft_strdup(data->env->pwd);
	chdir(cmd[1]);
	tmp = safe_getcwd(data->env->pwd);
	free(data->env->pwd);
	data->env->pwd = ft_strdup(tmp);
}


//void	init_dir_vars(t_gdata *data)
//{
//	data->env->home = ft_dup_var(&data->env->env_lst, "HOME");
//	data->env->home = ft_dup_var(&data->env->env_lst, "HOME");
//}

int	ft_cd(t_gdata *data, char **cmd)
{
	char			*tmp;

	//printf("---------DEBUUUUG--------");
	data->env->home = ft_dup_var(&data->env->env_lst, "HOME");
	//printf("%s\n", data->env->home);
	data->env->pwd = ft_dup_var(&data->env->env_lst, "PWD");
	if (ft_strlen(cmd[1]) > 255)
		return (put_cd_error(cmd[1], FILENAME));
	if ((!ft_strcmp(cmd[1], "~") || !cmd[1]))
		go_home(data, cmd);
	else
		go_path(data, cmd);
	check_var_replace(&data->env->env_lst, "PWD", data->env->pwd);
	check_var_replace(&data->env->env_lst, "OLDPWD", data->env->old_pwd);
	//TODO-> LIBERAR ENV struct
	//free()
	return (EXIT_SUCCESS);
}
