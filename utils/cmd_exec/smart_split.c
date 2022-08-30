/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:11:50 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/24 14:14:49 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	*append_free(int *index, int new)
{
	int	ind;
	int	*ret;

	ind = 0;
	while (index[ind] != -1)
		ind++;
	ret = (int *)malloc(sizeof(int) * (ind + 2));
	ret[ind + 1] = -1;
	ret[ind] = new;
	while (--ind >= 0)
		ret[ind] = index[ind];
	free(index);
	return (ret);
}

static int	*index_str(int *index, char *order, char limit)
{
	char	limiter;

	index = append_free(index, index[0]);
	index[1]++;
	limiter = '\0';
	while (order[index[0]] && (order[index[0]] != limit || limiter))
	{
		if (order[index[0]] == '\'' || order[index[0]] == '\"')
		{
			if (!limiter)
				limiter = order[index[0]];
			else if (order[index[0]] == limiter)
				limiter = '\0';
		}
		index[0]++;
	}
	index = append_free(index, index[0]);
	while (order[index[0]] && order[index[0]] == limit)
		index[0]++;
	if (!order[index[0]])
		return (index);
	return (index_str(index, order, limit));
}

char	**smart_split(char *order, char limit)
{
	int		*index;
	char	**ret;
	int		ind;
	int		ind2;

	index = (int *)malloc(sizeof(int) * 3);
	index[0] = 0;
	index[1] = 0;
	index[2] = -1;
	order = ft_strtrim(order, " ");
	index = index_str(index, order, limit);
	ret = (char **)malloc(sizeof(char *) * (index[1] + 1));
	ind = 2;
	ind2 = 0;
	while (index[ind] != -1)
	{
		ret[ind2++] = ft_substr(order, index[ind], \
		(index[ind + 1] - index[ind]));
		ind += 2;
	}
	ret[ind2] = NULL;
	free(order);
	free(index);
	return (ret);
}
