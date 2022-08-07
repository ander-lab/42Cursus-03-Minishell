/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:25:03 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/07 16:49:06 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*safe_getcwd(char *current_cwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (current_cwd);
	return (pwd);
}

//t_list	*ft_lstnew_struct(void *newcontent, size_t size)
//{
//	t_list	*new;
//	void	*content;
//
//	new = malloc(sizeof(t_list));
//	if (!new || !newcontent)
//		return (0);
//	content = malloc(size);
//	if (!content)
//	{
//		free(new);
//		return (0);
//	}
//	ft_memcpy(content, newcontent, size);
//	new->content = content;
//	new->next = NULL;
//	return (new);
//}

char	*ft_strjoin_token(char const *s1, char const *s2, char token)
{
	char	*sjoin;
	int		i;
	int		aux_s2;

	if (!s1 || !s2)
		return (0);
	sjoin = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!sjoin)
		return (0);
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

void	envp_to_lst(char **envp, t_list **lst_env)
{
	size_t ei;
	size_t matrix_len;
	char		**splitted_env_str;
	t_env_line *env_struct;

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
		ft_lstadd_back(lst_env, ft_lstnew_struct(env_struct, sizeof(t_env_line)));
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
//		free((*lst));
	}
//	printf("-----------LEAKKKKKKKKKKKKKKKKKKKKKKKKK----------\n");
//	leaks();
	//free((lst));
	//*lst = NULL;
}

void	lst_to_envmtrx(t_list *lst_env, t_gdata *gdata)
{
	int i = 0;

	//size_t	aux;

	//if (gdata->env->envp)
	ft_free_matrix(gdata->env->envp);
	//printf(" LST = %i \n  MATRIX = %zu\n", ft_lstsize(lst_env), ft_matrixlen(gdata->env->envp));
	gdata->env->envp = malloc(ft_lstsize(lst_env) * (sizeof(char *) + 1));
	//ft_printkey(lst_env);
	while (lst_env)
	{
		gdata->env->envp[i] = ft_strjoin_token(((t_env_line *)lst_env->content)->key, ((t_env_line *)lst_env->content)->value, '=');
		lst_env = lst_env->next;
		i++;
	}
	gdata->env->envp[i] = NULL;
}


//int main(int ac, char **av, char **env)
//{
//	t_env_line	*env_struct;
//
//	ac += 0;
//	av += 0;
//
//	atexit(leaks);
//	t_list *lst_env = NULL;
//	env_struct = malloc(sizeof(t_env_line) + 1);
//	if (!env_struct)
//		return (0);
//	envp_to_lst(env, &lst_env);
//	ft_printdlst(lst_env);
//	env = lst_to_envmtrx(lst_env, env);
//	//ft_putmatrix(env, ft_matrixlen(env));
//	ft_lstfree(lst_env);
//	ft_free_matrix(env);
//	free(env_struct);
//	return (0);
//}
