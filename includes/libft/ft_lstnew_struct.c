/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:38:58 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/27 12:06:27 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_struct(void *newcontent, size_t size)
{
	t_list	*new;
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
