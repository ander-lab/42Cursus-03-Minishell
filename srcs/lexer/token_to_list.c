/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:39:30 by ajimenez          #+#    #+#             */
/*   Updated: 2022/03/01 12:51:02 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*ft_lstnew_struct(void *newcontent, size_t size)
{
	t_list	*new;
	void	*content;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	content = malloc(size);
	if (!content)
	{
		free(new);
		return (NULL);
	}
	ft_memcpy(content, newcontent, size);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_insert_data_lst(t_list **lst, t_token_data *token_data, int *tokens, int len)
{
	int	aux;

	aux = 0;
	while (aux < len)
	{
		token_data->token = tokens[aux];
		ft_lstadd_back(lst, ft_lstnew_struct(token_data, sizeof(t_token_data)));
		aux++;
	}
}

static void	ft_strdup_on_lst(t_list **lst, char *str)
{
	if (!*lst || !str)
		return ;
	((t_token_data *)(*lst)->content)->str = ft_strdup(str);
}

void	ft_convert_matrix(char **words, t_list *lst)
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
