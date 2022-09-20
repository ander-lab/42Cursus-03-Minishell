/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:20:21 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/07 15:42:28 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_matrixlen(char **matrix)
{
	size_t	len;

	if (!matrix)
		return (0);
	len = 0;
	while (matrix[len] && matrix)
		len++;
	return (len);
}
