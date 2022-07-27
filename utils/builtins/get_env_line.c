/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:11:56 by ajimenez          #+#    #+#             */
/*   Updated: 2022/06/07 12:58:29 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char	*find_env_var(char **env, char *var)
{
	size_t	i;
	char	*line;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], var) == 0)
			line = ft_strdup(ft_strchr(env[i], '='));
		i++;
	}
	return (line);
}
