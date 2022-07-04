/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:37:10 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/04 15:18:07 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_infile(t_dlist *aux)
{
	int	tkn;
	int	it_is;

	it_is = 0;
	tkn = ((t_token_data *)aux->content)->token;
	if (tkn == 1)
		it_is = 1;
	return (it_is);
}

void	infile_checker(t_dlist *lst, t_gdata *gdata)
{
	char	*file;

	lst = lst->next;
	file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	if (access(file, F_OK) != 0)
	{
		gdata->inf_err = 1;
		perror(file);
	}
}

t_dlist *do_infile(t_dlist *lst)
{
	char	*file;

	while (is_infile(lst))
	{
		lst = lst->next;
		file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
		/*
		lst->ind = handle_file_no_create(file);
		*/
		/*if (gdata->fd[0] == -1)
			gdata->err = 1;*/
		lst = lst->next;
	}
	return (lst);
}

/*void	do_infile(t_dlist *aux, t_gdata *gdata)
{
	char	*cmd;

	aux = aux->next;
	cmd = ft_strtrim((((t_token_data *)aux->content)->str), " ");
	cmd = ft_strtrim(cmd, " ");
	gdata->fd[0] = handle_file_no_create(cmd);
	if (gdata->fd[0] == -1)
		gdata->err = 1;
}*/
