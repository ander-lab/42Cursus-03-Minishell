/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:41:33 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/29 12:39:34 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtin(t_cmds *cmds, t_gdata *gdata, char *cmd)
{
	char	*builtin;

	builtin = cpy_until_space(cmd);
	if (!ft_strncmp("echo", builtin, ft_strlen("echo")))
		ft_echo(ft_split(cmd, ' '), cmds->red);
	else if (!ft_strncmp("env", builtin, ft_strlen("env")))
		ft_env(gdata->envp, ft_split(cmd, ' '));
	else if (!ft_strncmp("exit", builtin, ft_strlen("exit")))
		ft_exit(ft_split(cmd, ' '));
	else if (!ft_strncmp("pwd", builtin, ft_strlen("pwd")))
		ft_pwd();
	else if (!ft_strncmp("export", builtin, ft_strlen("export")))
		ft_export(&gdata->env->env_lst, ft_split(cmd, ' '));
	else if (!ft_strncmp("unset", builtin, ft_strlen("unset")))
		ft_unset(&gdata->env->env_lst, ft_split(cmd, ' '));
}

static int cmp_builtin(char *builtin, char *s)
{
	if (!ft_strncmp(builtin, s, ft_strlen(s)) \
			&& !ft_strncmp(builtin, s, ft_strlen(builtin)))
		return (0);
	return (1);
}

int		is_builtin(char *cmd)
{
	char	*builtin;

	if (!cmd)
		return (0);
	builtin = cpy_until_space(cmd);
	if (!cmp_builtin("echo", builtin)
		|| !cmp_builtin("cd", builtin)
		|| !cmp_builtin("pwd", builtin)
		|| !cmp_builtin("export", builtin)
		|| !cmp_builtin("unset", builtin)
		|| !cmp_builtin("env", builtin)
		|| !cmp_builtin("exit", builtin))
		return (1);
	free(builtin);
	return (0);
}
