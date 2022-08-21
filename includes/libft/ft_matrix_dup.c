/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:55:10 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/21 12:39:37 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	**ft_matrix_dup(char **matrix, size_t lines)
{
	 size_t	i;
	 char 	**dup;
	 
	i = 0;
	dup = malloc((lines + 1) * sizeof(char *));
	while (i < lines)
	{
		dup[i] = ft_strdup(matrix[i]);
		i++;
		//dup[i] = NULL;
	}
	dup[i] = NULL;
	return (dup);
}
