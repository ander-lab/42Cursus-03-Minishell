/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:39:30 by ajimenez          #+#    #+#             */
/*   Updated: 2022/09/12 14:47:42 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_insert_data_lst(t_dlist **lst, t_token_data *token_data,
		int *tokens, int len)
{
	int	aux;

	aux = 0;
	while (aux < len)
	{
		token_data->token = tokens[aux];
		ft_dlstadd_back(lst, ft_dlstnew_struct(token_data,
				sizeof(t_token_data)));
		aux++;
	}
}

static void	ft_strdup_on_lst(t_dlist **lst, char *str)
{
	if (!*lst || !str)
		return ;
	((t_token_data *)(*lst)->content)->str = ft_strtrim(str, " ");
}

void	ft_convert_matrix(char **words, t_dlist *lst)
{
	int	aux;

	aux = 0;
	while (lst && words[aux])
	{
		if (((t_token_data *)lst->content)->token == -1)
		{
			ft_strdup_on_lst(&lst, words[aux]);
			aux++;
		}
		lst = lst->next;
	}
}
