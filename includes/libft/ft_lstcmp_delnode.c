/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcmp_delnode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:49:02 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/04 14:23:17 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

static int del_first(t_list **lst, char *str ,int (*f)(const char *, const char *))
{
	t_list *aux_iter;

	aux_iter = *lst;
	if (f((char *)aux_iter->content, str))
	{
		*lst = (*lst)->next;
		//free(aux_iter->content);
		free(aux_iter);
		//printf("%p\n %p\n", aux_iter, aux_iter->content);
		return (1);
	}
	return (0);
}

void	ft_lstcmp_delnode(t_list **lst, char *str ,int (*f)(const char *, const char *))
{
	t_list	*aux_iter;
	t_list	*tmp;

	if (!lst || !*lst || !f)
		return ;
	if (del_first(lst, str, f))
		return ;
	aux_iter = *lst;
	tmp = aux_iter;
	while (aux_iter)
	{
		if (f((char *)aux_iter->content, str))
		{
			tmp->next = aux_iter->next;
			//free(aux_iter->content);
			free(aux_iter);
			return ;
		}
		tmp = aux_iter;
		aux_iter= aux_iter->next;
	}
//	printf("NO EXISTE\n");
}
