/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:13:27 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/22 14:04:28 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_val_length(char *val)
{
	int	l;
	int	i;

	i = 0;
	l = 0;
	while (val[i])
	{
		if (val[i] == '=')
			break ;
		i++;
	}
	while (val[++i])
		l++;
	return (l);
}

char	*get_env_val(char *cmd, char **envp)
{
	int		i;
	char	*val;
	int		x;
	int		z;

	i = 0;
	x = -1;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], cmd, ft_strlen(cmd)) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (0);
	val = ft_calloc(sizeof(char), env_val_length(envp[i]) + 1);
	if (!val)
		return (0);
	z = 0;
	while (envp[i][z] != '=')
		z++;
	while (envp[i][z])
		val[++x] = envp[i][++z];
	return (val);
}
