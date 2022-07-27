/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:12:53 by ajimenez          #+#    #+#             */
/*   Updated: 2022/06/14 09:56:57 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char **build_env(void)
{
	char	**oenv;
	
	oenv[0] = ft_strdup(ft_strjoin("PWD=", getcwd(NULL, 0)));
	oenv[1] = ft_strdup("SHLVL=1");
	return (oenv);
}

char	**create_env(char **envp)
{
	if (!*envp)
		return (build_env());
	else
		return (envp);
}
//TODO -> Sumar el shlvl 
