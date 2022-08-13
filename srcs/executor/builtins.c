/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:41:33 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/10 15:51:23 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_printkey(t_list *token_lst)
{
	printf("\n");
	printf("\n");
	while (token_lst)
	{
		printf("%s=", ((t_env_line *)token_lst->content)->key);
		printf("%s\n", ((t_env_line *)token_lst->content)->value);
		//token_data = token_lst->content;
		//printf(" token 2= %i\n", token_data->token);
		token_lst = token_lst->next;
	}
}
void	execute_builtin(t_cmds *cmds, t_gdata *gdata)
{
	char	*builtin;
	char	*cmd;

	cmd = (char *)cmds->content;
	builtin = cpy_until_space(cmd);
	if (!ft_strncmp("echo", builtin, ft_strlen("echo")))
		ft_echo(ft_split(cmd, ' '), gdata, cmds->red);
	else if (!ft_strncmp("env", builtin, ft_strlen("env")))
		ft_env(gdata, ft_split(cmd, ' '), cmds->red);
	else if (!ft_strncmp("exit", builtin, ft_strlen("exit")))
		ft_exit(ft_split(cmd, ' '), gdata);
	else if (!ft_strncmp("pwd", builtin, ft_strlen("pwd")))
		ft_pwd(gdata, cmds->red);
	else if (!ft_strncmp("export", builtin, ft_strlen("export")))
		ft_export(&gdata->env->env_lst, ft_split(cmd, ' '));
	else if (!ft_strncmp("unset", builtin, ft_strlen("unset")))
		ft_unset(&gdata->env->env_lst, ft_split(cmd, ' '));
	else if (!ft_strncmp("cd", builtin, ft_strlen("cd")))
		ft_cd(gdata, ft_split(cmd, ' '));
//TODO-> FUNCION QUE EXPORTE HOME
	lst_to_envmtrx(gdata->env->env_lst, gdata);
//	ft_lstfree(gdata->env->env_lst);
	//envp_to_lst(gdata->env->envp, &gdata->env->env_lst);
//	printf("\n");
//	ft_putmatrix(gdata->env->envp, ft_matrixlen(gdata->env->envp));
//	printf("\n");
//	printf("------------------------------------------------------------------------------");
//	printf("\n");
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
	{
		return (1);
	}
	free(builtin);
	return (0);
}
