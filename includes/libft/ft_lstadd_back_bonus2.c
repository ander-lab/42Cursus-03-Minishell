/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:48:14 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/05 11:55:15 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back2(t_cmds **lst, t_cmds *new)
{
	t_cmds	*back;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	back = ft_dlstlast2(*lst);
	back->next = new;
}
