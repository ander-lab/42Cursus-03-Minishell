/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:41:24 by ajimenez          #+#    #+#             */
/*   Updated: 2022/06/15 10:54:19 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	len_to_token(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static t_dlist	*env_exist(char **cmd, t_dlist *env)
{
	while (env)
	{
		if (ft_strncmp(cmd[1], (char *)env->content,
			len_to_token((char *)env->content, '=')))
			return (env);
		env = env->next;
	}	
	return (NULL);
}

static void	replace_var(t_dlist **env, char *new_var)
{
	free((*env)->content);
	(*env)->content = ft_dlstnew(new_var);
}

int ft_export(t_env *env, char **cmd)	
{
	t_matrix_data matrix_data;

	matrix_data = ft_matrix_data(cmd);
	if (matrix_data.line_count == 0)
		ft_putstr_fd("\n", 1);
	else
		env_exist(cmd, (t_dlist *)env->env_lst);
}
