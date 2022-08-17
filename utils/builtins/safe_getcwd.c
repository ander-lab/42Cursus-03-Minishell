/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_getcwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 20:04:14 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/15 20:04:35 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*safe_getcwd(char *current_cwd)
{
	char	*pwd;

	pwd = getcwd(NULL, FILENAME_MAX);
	if (!pwd)
		return (current_cwd);
	return (pwd);
}
