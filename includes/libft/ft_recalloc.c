/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:14:13 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/23 15:15:46 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_recalloc(void *ptr, size_t size)
{
	if (!ptr)
		return (0);
	free(ptr);
	ptr = (void *)ft_calloc(size, 1);
	return (ptr);
}
