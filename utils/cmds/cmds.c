/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:58:00 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/18 15:06:18 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	last_infile(t_dlist *lst)
{
	char	*file;
	int		fd;

	fd = -1;
	if (lst->prev)
		lst = lst->prev;
	file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	if (file)
		fd = handle_file_no_create(file);
	return (fd);
}

int	last_red(t_dlist *lst, int red)
{
	char	*file;
	int		fd;
	int		prev;

	fd = -1;
	if (!red)
		return (fd);
	prev = get_prev_type(lst);
	file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	if (prev == 2)
		fd = handle_file_create(file, 0);
	else if (prev == 4)
		fd = handle_file_create(file, 1);
	return (fd);
}

int	exist_red(t_dlist *lst)
{
	int	prev;
	int	exists;

	exists = 0;
	prev = get_prev_type(lst);
	if (prev == 2 || prev == 4)
		exists = 1;
	return (exists);
}

int	get_ind(t_dlist *lst)
{
	int		tkn;
	int		ind;
	char	*file;

	ind = -1;
	tkn = (((t_token_data *)lst->content)->token);
	while (lst && tkn != 0)
	{
		if (tkn == 1)
		{
			lst = lst->next;
			file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
			ind = handle_file_no_create(file);
			free(file);
		}
		lst = lst->next;
		if (lst)
			tkn = (((t_token_data *)lst->content)->token);
	}
	return (ind);
}

int	get_red(t_dlist *lst)
{
	int		tkn;
	int		red;
	char	*file;

	red = -1;
	tkn = (((t_token_data *)lst->content)->token);
	while (lst && tkn != 0)
	{
		if (tkn == 2 || tkn == 4)
		{
			lst = lst->next;
			file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
			if (tkn == 2)
				red = handle_file_create(file, 0);
			if (tkn == 4)
				red = handle_file_create(file, 1);
			free(file);
		}
		lst = lst->next;
		if (lst)
			tkn = (((t_token_data *)lst->content)->token);
	}
	return (red);
}
