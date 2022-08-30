/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 20:45:51 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/21 18:57:09 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
