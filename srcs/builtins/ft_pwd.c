/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:51:36 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/09 17:22:47 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_gdata *data)
{
	char	*pwd;

	//pwd = safe_getcwd(current_cwd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_dup_var(&data->env->env_lst, "PWD");
	printf("%s\n", pwd);
	free (pwd);
	return (EXIT_SUCCESS);
}
