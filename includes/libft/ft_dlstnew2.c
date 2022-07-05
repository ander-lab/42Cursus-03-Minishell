/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:59:29 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/05 12:42:45 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_cmds *ft_dlstnew2(void *content)
{
	t_cmds	*lstnew;

	lstnew = malloc(sizeof(t_cmds));
	if (!lstnew)
		return (0);
	lstnew->content = content;
	lstnew->ind = -1;
	lstnew->red = -1;
	lstnew->next = NULL;
	return (lstnew);
}
