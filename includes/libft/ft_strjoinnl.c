/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinnl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:29:23 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/01 16:41:54 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinnl(char const *s1, char const *s2)
{
	char	*sjoin;
	int		i;
	int		aux_s2;

	if (!s1 || !s2)
		return (0);
	sjoin = (char *)malloc(ft_strlen(s1) + 1 + ft_strlen(s2) + 1);
	if (!sjoin)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		sjoin[i] = s1[i];
		i++;
	}
	sjoin[i++] = '\n';
	aux_s2 = 0;
	while (s2[aux_s2] != '\0')
	{
		sjoin[i] = s2[aux_s2];
		i++;
		aux_s2++;
	}
	sjoin[i] = '\0';
	return (sjoin);
}
