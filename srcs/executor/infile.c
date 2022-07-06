/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:37:10 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/06 15:56:33 by goliano-         ###   ########.fr       */
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

/*void	infile_checker(t_dlist *lst, t_gdata *gdata)
{
	char	*file;
	int		tkn;

	lst = lst->next;
	file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	lst = lst->next;
	tkn = ((t_token_data *)lst->content)->token;
	while (tkn == 1)
	{
		lst = lst->next;
		tkn = ((t_token_data *)lst->content)->token;
	}
	if (access(file, F_OK) != 0)
	{
		lst = lst->next;
		if (tkn == 0)
			gdata->inf_err = 0;
		else
			gdata->inf_err = 1;
		perror(file);
	}
}*/

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
	printf("NEX: %d\n", next);
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

	while (is_infile(lst) && !gdata->inf_err)
	{
		lst = lst->next;
		file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
		if (file_checker(file) && do_inf_err(file, lst))
			gdata->inf_err = 1;
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
