/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:14:29 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/20 14:14:48 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_cd(t_gdata *gdata)
{
	if (gdata->env->home)
		free(gdata->env->home);
	if (gdata->env->pwd && *gdata->env->pwd)
		free(gdata->env->pwd);
	gdata->env->home = ft_dup_var(&gdata->env->env_lst, "HOME");
	gdata->env->pwd = ft_dup_var(&gdata->env->env_lst, "PWD");
}
