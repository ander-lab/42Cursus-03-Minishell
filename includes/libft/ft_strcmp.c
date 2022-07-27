/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:16:19 by ajimenez          #+#    #+#             */
/*   Updated: 2022/06/08 13:57:55 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *src, const char *to_cmp)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_strlen(src);
	while (src[i] != '\0' && to_cmp[i] != '\0' && i < n)
	{
		if (src[i] != to_cmp[i])
			return ((unsigned char)src[i] - (unsigned char)src[i]);
		++i;
	}
	if (i != n)
		return ((unsigned char)src[i] - (unsigned char)to_cmp[i]);
	return (0);
}
