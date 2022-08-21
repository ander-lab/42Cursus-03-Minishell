/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 20:46:07 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/21 12:20:17 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char	*ft_strjoin_token(char const *s1, char const *s2, char token)
{
	char	*sjoin;
	int		i;
	int		aux_s2;

	if (!s1 || !s2)
		return (0);
	sjoin = (char *)ft_calloc(ft_strlen(s1), ft_strlen(s2) + 3);
	i = 0;
	while (s1[i] != '\0')
	{
		sjoin[i] = s1[i];
		i++;
	}
	sjoin[i] = token;
	i++;
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
