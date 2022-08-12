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

int	ft_pwd(t_gdata *gdata, int red)
{
	char	*pwd;

	output_type(gdata, red);
	//pwd = safe_getcwd(current_cwd);
	pwd = getcwd(NULL, 0);
	print_built_out(pwd, gdata, red);
	print_built_out("\n", gdata, red);
	free (pwd);
	return (EXIT_SUCCESS);
}
