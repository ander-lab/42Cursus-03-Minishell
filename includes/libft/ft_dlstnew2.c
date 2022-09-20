/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:59:29 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/24 00:36:21 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_cmds	*ft_dlstnew2(t_cmds *cmds)
{
	t_cmds	*lstnew;

	lstnew = malloc(sizeof(t_cmds));
	if (!lstnew)
		return (0);
	lstnew->content = cmds->content;
	lstnew->ind = cmds->ind;
	lstnew->red = cmds->red;
	lstnew->next = NULL;
	return (lstnew);
}
