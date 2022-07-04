/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:25:03 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/04 15:28:07 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*safe_getcwd(char *current_cwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (current_cwd);
	return (pwd);
}
