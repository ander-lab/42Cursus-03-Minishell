/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 17:09:37 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/30 10:29:51 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_search_length(char *cmd)
{
	int		i;
	int		l;

	if (!cmd)
		return (0);
	i = -1;
	l = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '$')
			break ;
	}
	while (cmd[i] && !is_quote(cmd[i]))
	{
		i++;
		l++;
	}
	return (l);
}

char	*get_env_search(char *cmd)
{
	int		i;
	int		x;
	char	*search;

	if (!cmd)
		return (0);
	i = -1;
	x = -1;
	search = calloc(sizeof(char), env_search_length(cmd) + 1);
	if (!search)
		return (0);
	while (cmd[++i])
	{
		if (cmd[i] == '$')
			break ;
	}
	while (cmd[i] && !is_quote(cmd[i]))
		search[++x] = cmd[++i];
	search[x] = '=';
	search[x + 1] = '\0';
	return (search);
}

char	*expansion_output(char *cmd, char *val)
{
	char	*out;
	int		i;
	int		x;
	int		z;

	out = ft_calloc(sizeof(char *), ft_strlen(val) + ft_strlen(cmd));
	if (!out)
		return (0);
	i = -1;
	x = -1;
	z = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '$')
			break ;
		out[++x] = cmd[i];
	}
	while (val[++z])
		out[++x] = val[z];
	while (cmd[++i])
	{
		if (is_quote(cmd[i]))
			out[++x] = cmd[i];
	}
	return (out);
}

char	*handle_expansion(t_cmds *cmds, char **envp)
{
	char	*cmd;
	char	*val;

	cmd = (char *)cmds->content;
	val = get_env_val(get_env_search(cmd), envp);
	if (!val)
		return (0);
	return (expansion_output(cmd, val));
}
