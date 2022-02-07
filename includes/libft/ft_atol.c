/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:40:24 by ajimenez          #+#    #+#             */
/*   Updated: 2021/12/09 10:40:25 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long int	ft_atol(const char *str)
{
	int				i;
	int				s;
	unsigned int	r;

	i = 0;
	s = 1;
	r = 0;
	while (str[i] <= 13 || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - '0');
		if (r > 2147483647 && s == 1)
			return (-1);
		if (r > 2147483648 && s == -1)
			return (0);
		i++;
	}
	return (r * s);
}
