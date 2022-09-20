/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_getcwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 20:46:37 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/20 16:42:31 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*safe_getcwd(char *current_cwd, int *i)
{
	char	*pwd;

	pwd = getcwd(NULL, FILENAME_MAX);
	current_cwd += 0;
	if (!pwd)
	{
		*i = 1;
		return (current_cwd);
	}
	return (pwd);
}
