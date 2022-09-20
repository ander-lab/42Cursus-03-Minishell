/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:41:33 by goliano-          #+#    #+#             */
/*   Updated: 2022/09/20 16:50:42 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	free_exit(char *cmd, t_gdata *gdata, int *pids, char *builtin)
{
	free(builtin);
	ft_exit(ft_split(cmd, ' '), gdata, pids);
	return (1);
}

static void	call_builtin(char *cmd, t_gdata *gdata, int red, int t)
{
	if (t == 1)
	{
		ft_export(red, ft_split(cmd, ' '), gdata);
		lst_to_envmtrx(gdata->env->env_lst, gdata);
	}
	else if (t == 2)
	{
		ft_cd(gdata, ft_split(cmd, ' '));
		lst_to_envmtrx(gdata->env->env_lst, gdata);
	}
	else
	{
		ft_unset(&gdata->env->env_lst, ft_split(cmd, ' '));
		lst_to_envmtrx(gdata->env->env_lst, gdata);
	}
}

void	execute_builtin(t_cmds *cmds, t_gdata *gdata, int *pids)
{
	char	*builtin;
	char	*cmd;
	int		aux_free;

	aux_free = 0;
	cmd = (char *)cmds->content;
	builtin = cpy_until_space(cmd);
	if (!ft_strncmp("echo", builtin, ft_strlen("echo")))
		ft_echo(ft_split(cmd, ' '), gdata, cmds->red);
	else if (!ft_strncmp("env", builtin, ft_strlen("env")))
		ft_env(ft_split(cmd, ' '), gdata, cmds->red, 1);
	else if (!ft_strncmp("pwd", builtin, ft_strlen("pwd")))
		ft_pwd(gdata, cmds->red);
	else if (!ft_strncmp("export", builtin, ft_strlen("export")))
		call_builtin(cmd, gdata, cmds->red, 1);
	else if (!ft_strncmp("unset", builtin, ft_strlen("unset")))
		call_builtin(cmd, gdata, cmds->red, 0);
	else if (!ft_strncmp("cd", builtin, ft_strlen("cd")))
		call_builtin(cmd, gdata, cmds->red, 2);
	else if (!ft_strncmp("exit", builtin, ft_strlen("exit")))
		aux_free = free_exit(cmd, gdata, pids, builtin);
	if (aux_free == 0)
		free(builtin);
}

static	int	cmp_builtin(char *builtin, char *s)
{
	if (!ft_strncmp(builtin, s, ft_strlen(s)) \
			&& !ft_strncmp(builtin, s, ft_strlen(builtin)))
		return (0);
	return (1);
}

int	is_builtin(char *cmd)
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
	{
		free(builtin);
		return (1);
	}
	free(builtin);
	return (0);
}
