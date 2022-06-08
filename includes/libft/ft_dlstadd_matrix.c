/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:41:05 by ajimenez          #+#    #+#             */
/*   Updated: 2022/06/08 14:04:43 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_matrix_to_dlst(t_dlist **dlst, char **matrix)
{
	int	aux;
	t_matrix_data data;

	aux = 0;
	data = ft_matrix_data(matrix);
	while (aux < data.line_count)
	{
		ft_dlstadd_back(dlst, ft_dlstnew(matrix[aux]));
		aux++;
	}
}
