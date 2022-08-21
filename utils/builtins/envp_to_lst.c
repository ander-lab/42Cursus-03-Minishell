/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 20:45:20 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/20 20:47:22 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

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
