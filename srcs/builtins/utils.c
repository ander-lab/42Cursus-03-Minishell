/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:25:03 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/20 20:50:22 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

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
