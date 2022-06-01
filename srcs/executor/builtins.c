/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:41:33 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/01 12:14:56 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtin(t_gdata *gdata, char *cmd)
{
	char	*builtin;

	builtin = cpy_until_space(cmd);
	if (!ft_strncmp("echo", builtin, ft_strlen("echo")))
		ft_echo(ft_split(cmd, ' '));
	else if (!ft_strncmp("env", builtin, ft_strlen("env")))
		ft_env(gdata->envp, ft_split(cmd, ' '));
	else if (!ft_strncmp("exit", builtin, ft_strlen("exit")))
		ft_exit(ft_split(cmd, ' '));
	else if (!ft_strncmp("pwd", builtin, ft_strlen("pwd")))
		ft_pwd();
}

int		is_builtin(char *cmd)
{
	int		it_is;
	char	*builtin;

	it_is = 0;
	if (!cmd)
		return (it_is);
	builtin = cpy_until_space(cmd);
	if (!ft_strncmp("echo", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("echo", builtin, ft_strlen("echo")))
		it_is = 1;
	else if (!ft_strncmp("cd", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("cd", builtin, ft_strlen("cd")))
		it_is = 1;
	else if (!ft_strncmp("pwd", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("pwd", builtin, ft_strlen("pwd")))
		it_is = 1;
	else if (!ft_strncmp("export", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("export", builtin, ft_strlen("export")))
		it_is = 1;
	else if (!ft_strncmp("unset", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("unset", builtin, ft_strlen("unset")))
		it_is = 1;
	else if (!ft_strncmp("env", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("env", builtin, ft_strlen("env")))
		it_is = 1;
	else if (!ft_strncmp("exit", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("exit", builtin, ft_strlen("exit")))
		it_is = 1;
	free(builtin);
	return (it_is);
}
