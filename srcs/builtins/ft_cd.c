/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:29:37 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/09 16:20:49 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO -> MAX FILE NAME ES 255 en bash

int		max_name(char *file)
{
	ft_putstr_fd(file, 1);
	ft_putstr_fd(": File name too long", 1);
	return (0);
}

void	go_home(t_gdata *data, char **args)
{
	char	*tmp;

	if (!data->env->home)
		ft_putstr_fd("minishell: cd: HOME not set", 2);
	tmp = ft_strdup(data->env->pwd);
	data->env->old_pwd = ft_strdup(tmp);
	free(data->env->pwd);
	data->env->pwd = ft_strdup(data->env->home);
	chdir(data->env->pwd);
	free(tmp);
}

void	go_path(t_gdata *data, char **cmd)
{
	char *tmp;

	data->env->old_pwd = ft_strdup(data->env->pwd);
	chdir(cmd[1]);
	tmp = safe_getcwd(data->env->pwd);
	free(data->env->pwd);
	data->env->pwd = ft_strdup(tmp);
}

char	*ft_dup_var(t_list **lst, char *key)
{
	t_list	*aux_iter;
	char	*var;

	if (!lst || !*lst)
		return (0);
	aux_iter = *lst;
	while (aux_iter)
	{
		if (!ft_strcmp((((t_env_line *)(aux_iter)->content)->key), key))
		{
			var = ft_strdup(((t_env_line *)(aux_iter)->content)->value);
			return (var);
		}
		aux_iter = aux_iter->next;
	}
	return (0);
}

//void	init_dir_vars(t_gdata *data)
//{
//	data->env->home = ft_dup_var(&data->env->env_lst, "HOME");
//	data->env->home = ft_dup_var(&data->env->env_lst, "HOME");
//}

int	ft_cd(t_gdata *data, char **cmd)
{
	char			*tmp;

	printf("---------DEBUUUUG--------");
	data->env->home = ft_dup_var(&data->env->env_lst, "HOME");
	printf("%s\n", data->env->home);
	data->env->pwd = ft_dup_var(&data->env->env_lst, "PWD");
	if (ft_strlen(cmd[1]) > 255)
		return (max_name(cmd[1]));
	if ((!ft_strcmp(cmd[1], "~") || !cmd[1]))
		go_home(data, cmd);
	if ((!ft_strcmp(cmd[1], "~") || !cmd[1]))
		go_path(data, cmd);
	return (EXIT_SUCCESS);
}
