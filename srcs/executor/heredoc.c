/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:32:42 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/17 15:38:47 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_dlist	*go_to_cmd(t_dlist *lst)
{
	int	tkn;
	
	while (lst)
	{
		lst = lst->prev;
		lst = lst->prev;
		if (!lst->prev)
			return (lst);
		lst = iterate_red_app(lst);
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 6)
			return (lst);
		lst = iterate_ind(lst);
		if (tkn == 3)
			lst = lst->next;
		lst = lst->prev;
	}
	return (lst);
}

t_dlist *go_last_here(t_dlist *lst)
{
	t_dlist	*aux;
	int	tkn;

	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
		{
			aux = lst;
			while (lst)
			{
				tkn = ((t_token_data *)lst->content)->token;
				if (tkn == 3)
					break ;
				lst = lst->next;
			}
			lst = aux;
		}
		lst = lst->next;
	}
	return (aux->next);
}

int	red_app_handler(t_dlist *lst, t_gdata *gdata)
{
	char	*file;
	int		fd;
	int		red;
	int		next_type;

	fd = 1;
	red = 0;
	file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	next_type = get_next_type(lst);
	if (next_type == 2 || next_type == 4)
	{
		lst = lst->next->next;
		file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
		if (next_type == 2)
			fd = handle_file_create(file, 0);
		else
			fd = handle_file_create(file, 1);
		next_type = get_next_type(lst);
		red = 1;
	}
	gdata->fd[1] = fd;
	return (red);
	/*while (next_type == 2 || next_type == 4)
	{
		lst = lst->next;
		lst = lst->next;
		file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
		if (next_type == 2)
			fd = handle_file_create(file, 0);
		else
			fd = handle_file_create(file, 1);
		next_type = get_next_type(lst);
		red = 1;
	}
	return (red);*/
}

void	do_heredoc(t_dlist *lst, t_gdata *gdata)
{
	char	*cmd;

	lst = go_heredoc(lst);
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	if (has_quotes(cmd))
		cmd = cpy_str_no_quotes(cmd);
	if (is_last_heredoc(lst) && need_exec(lst))
		do_here_cmd(lst, gdata);
	else
		fill_heredoc(gdata, cmd);
}
