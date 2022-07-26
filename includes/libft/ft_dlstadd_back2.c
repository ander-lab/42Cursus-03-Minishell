/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:56:57 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/06 12:11:49 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back2(t_cmds **dlst, t_cmds *new)
{
	t_cmds	*back;

	if (!new)
		return ;
	if (!*dlst)
	{
		*dlst = new;
		return ;
	}
	back = ft_dlstlast2(*dlst);
	back->next = new;
}
