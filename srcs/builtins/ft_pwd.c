/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:51:36 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/29 12:45:32 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd()
{
	char	*pwd;

	//pwd = safe_getcwd(current_cwd);
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free (pwd);
	return (EXIT_SUCCESS);
}
