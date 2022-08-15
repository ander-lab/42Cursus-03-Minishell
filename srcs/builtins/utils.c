/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:25:03 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/12 14:08:36 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

char	*ft_dup_var(t_list **lst, char *key)
{
	t_list	*aux_iter;
	char	*var;

	if (!lst || !*lst)
		return (0);
	aux_iter = *lst;
	while (aux_iter)
	{
		if (!ft_strcmp((((t_env_line *)(aux_iter)->content)->key), key))
		{
			var = ft_strdup(((t_env_line *)(aux_iter)->content)->value);
			return (var);
		}
		aux_iter = aux_iter->next;
	}
	return (0);
}

char	*safe_getcwd(char *current_cwd)
{
	char	*pwd;

	pwd = getcwd(NULL, FILENAME_MAX);
	if (!pwd)
		return (current_cwd);
	return (pwd);
}

char	*ft_strjoin_token(char const *s1, char const *s2, char token)
{
	char	*sjoin;
	int		i;
	int		aux_s2;

	if (!s1 || !s2)
		return (0);
	sjoin = (char *)ft_calloc(ft_strlen(s1), ft_strlen(s2) + 2);
	i = 0;
	while (s1[i] != '\0')
	{
		sjoin[i] = s1[i];
		i++;
	}
	sjoin[i] = token;
	i++;
	aux_s2 = 0;
	while (s2[aux_s2] != '\0')
	{
		sjoin[i] = s2[aux_s2];
		i++;
		aux_s2++;
	}
	sjoin[i] = '\0';
	return (sjoin);
}

void	envp_to_lst(char **envp, t_list **lst)
{
	size_t		ei;
	size_t		matrix_len;
	char		**splitted_env_str;
	t_env_line	*env_struct;

	ei = 0;
	matrix_len = ft_matrixlen(envp);
	env_struct = ft_calloc(sizeof(t_env_line), 1);
	if (!env_struct)
		return ;
	while (ei < matrix_len)
	{
		splitted_env_str = ft_split(envp[ei], '=');
		env_struct->key = ft_strdup(splitted_env_str[0]);
		env_struct->value = ft_strdup(splitted_env_str[1]);
		ft_lstadd_back(lst, ft_lstnew_struct(env_struct, sizeof(t_env_line)));
		ft_free_matrix(splitted_env_str);
		ei++;
	}
	free(env_struct);
}

void	ft_lstfree(t_list *lst)
{
	t_list	*aux;

	if (!lst)
		return ;
	while (lst)
	{
		aux = lst;
		free((((t_env_line *)aux->content)->key));
		free((((t_env_line *)aux->content)->value));
		free(aux->content);
		lst = lst->next;
		free(aux);
	}
}

void	lst_to_envmtrx(t_list *lst_env, t_gdata *gdata)
{
	int	i;

	i = 0;
	ft_free_matrix(gdata->env->envp);
	gdata->env->envp = malloc(ft_lstsize(lst_env) * (sizeof(char *) + 1));
	while (lst_env)
	{
		gdata->env->envp[i]
			= ft_strjoin_token(((t_env_line *)lst_env->content)->key,
				((t_env_line *)lst_env->content)->value,
				'=');
		lst_env = lst_env->next;
		i++;
	}
	gdata->env->envp[i] = NULL;
}
