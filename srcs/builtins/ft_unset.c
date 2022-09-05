/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:03:49 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/05 11:33:14 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	del_first(t_list **lst, char *str)
{
	t_list	*aux_iter;

	aux_iter = *lst;
	if (ft_strcmp((((t_env_line *)(*lst)->content)->key), str) == 0)
	{
		*lst = (*lst)->next;
		free(aux_iter);
		return (1);
	}
	return (0);
}

static void	ft_lstcmp_delnode(t_list **lst, char *str)
{
	t_list	*aux_iter;
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	if (del_first(lst, str))
		return ;
	aux_iter = *lst;
	tmp = aux_iter;
	while (aux_iter)
	{
		if (ft_strcmp((((t_env_line *)aux_iter->content)->key), str) == 0)
		{
			tmp->next = aux_iter->next;
			free(aux_iter);
			return ;
		}
		tmp = aux_iter;
		aux_iter = aux_iter->next;
	}
	printf("NO EXISTE\n");
}

int	ft_unset(t_list **env, char **cmd)
{
	if (ft_matrixlen(cmd) == 1)
	{
		ft_free_matrix(cmd);
		return (0);
	}
	else if (ft_matrixlen(cmd) > 1)
		ft_lstcmp_delnode(env, cmd[1]);
	ft_free_matrix(cmd);
	return (0);
}

//int	main(int ac, char **av, char **env)
//{
//	//av++;
//	ac += 0;
//	t_list *lst;
//	char *m[4];
//
//	m[0] = ft_strdup("HOLA=1");
//	m[1] = ft_strdup("PRUEBA=2");
//	m[2] = ft_strdup("LAST=1");
//	m[3] = NULL;
//	
//	lst = NULL;
//	//ft_matrix_to_dlst(&lst, m);
//	//env = lst_to_envmtrx(lst, env);
//	envp_to_lst(env, &lst);
//	
//	//ft_printdlst(lst);
//	ft_unset(&lst, av);
//	printf("\n--------------------------------------\n");
//	ft_printdlst(lst);
//}
