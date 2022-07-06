/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:19:09 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/06 12:24:39 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_cmds	*ft_dlstnew_struct2(void *newcontent, size_t size)
{
	t_cmds	*new;
	void	*content;

	new = malloc(sizeof(t_dlist));
	if (!new)
		return (0);
	content = malloc(size);
	if (!content)
	{
		free(new);
		return (0);
	}
	ft_memcpy(content, newcontent, size);
	new->content = content;
	new->next = NULL;
	return (new);
}
