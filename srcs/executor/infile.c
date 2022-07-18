/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:37:10 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/18 12:57:47 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_infile(t_dlist *aux)
{
	int	tkn;
	int	it_is;

	it_is = 0;
	if (!aux)
		return (it_is);
	tkn = ((t_token_data *)aux->content)->token;
	if (tkn == 1)
		it_is = 1;
	return (it_is);
}

void	handle_infile(t_dlist *lst, t_gdata *gdata)
{
	while (lst)
	{
		if (is_infile(lst))
			lst = do_infile(lst, gdata);
		else
			lst = lst->next;
	}
}

static int	file_checker(char *file)
{
	int	err;

	err = 0;
	if (access(file, F_OK) != 0)
		err = 1;
	return (err);
}

static int	do_inf_err(char *file, t_dlist *lst)
{
	int	next;

	next = get_next_type(lst);
	if (next != 0)
	{
		perror(file);
		return (1);
	}
	perror(file);
	return (0);
}

t_dlist *do_infile(t_dlist *lst, t_gdata *gdata)
{
	char	*file;

	while (is_infile(lst))
	{
		lst = lst->next;
		file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
		if (file_checker(file) && do_inf_err(file, lst))
			gdata->inf_err = 1;
		lst = lst->next;
	}
	return (lst);
}
