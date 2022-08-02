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

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{	
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/*int	ft_strcmp(const char *src, const char *to_cmp)
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
}*/
