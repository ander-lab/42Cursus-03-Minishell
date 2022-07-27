/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_struct2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 12:09:48 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/27 12:13:29 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_cmds	*ft_lstnew_struct_cmds(void *newcontent, size_t size)
{
	t_cmds	*new;
	void	*content;

	new = malloc(sizeof(t_list));
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
