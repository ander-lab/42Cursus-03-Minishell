/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:03:49 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/04 13:08:00 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	ft_unset(t_list	**env, char **cmd)
{
	if (ft_matrixlen(cmd) == 1)
	{
		return (0);
	}
	else if (ft_matrixlen(cmd) > 1)
		ft_lstcmp_delnode(env, cmd[1], ft_strcmp);
	return (0);
}
