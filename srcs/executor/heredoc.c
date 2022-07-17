/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:32:42 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/14 15:24:05 by goliano-         ###   ########.fr       */
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

/*t_dlist	*red_app_handler(t_dlist *lst)
{
	char	*file;
	int		fd;
	int		next_type;

	fd = -1;
	next_type = get_next_type(lst);
	while (next_type == 2 || next_type == 4)
	{
		lst = lst->next->next;
		file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
		if (next_type == 2)
			fd = handle_file_create(file, 0);
		else
			fd = handle_file_create(file, 1);
		next_type = get_next_type(lst);
		if (next_type != 2 && next_type != 4)
			lst = lst->next;
	}
	//gdata->fd[1] = fd;
	return (lst);*/
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
//}

int	heredoc_count(t_dlist *lst)
{
	int	c;
	int	tkn;
	int	next;

	c = 0;
	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
		{
			lst = lst->next;
			next = get_next_type(lst);
			if (next == 0 || next == -1)
				c++;
		}
		lst = lst->next;
	}
	return (c);
}

int	store_heredoc(t_dlist *lst)
{
	int	store;
	int	next;
	
	store = 0;
	next = get_next_type(lst);
	if (next == 0 || next == -1)
		store = 1;
	return (store);
}

void	do_heredoc(t_dlist *lst, t_gdata *gdata)
{
	char	*cmd;
	int		store;
	char	*here;
	int		x;

	//gdata->heredoc = ft_calloc(sizeof(char *), heredoc_count(lst) + 1);
	x = -1;
	while (exists_heredoc(lst))
	{
		lst = go_heredoc(lst);
		cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
		if (has_quotes(cmd))
			cmd = cpy_str_no_quotes(cmd);
		//if (is_last_heredoc(lst) && need_exec(lst))
		//	do_here_cmd(lst, gdata);
		//else
		store = store_heredoc(lst);
		here = fill_heredoc(cmd);
		if (store)
			gdata->heredoc[++x] = here;
			/*int fd = open("42heredoc", O_WRONLY | O_CREAT, 0644);
			if (fd < 0)
			{
				perror("42heredoc: ");
				return ;
			}
			printf("FD: %d\n", fd);
			write(fd, here, ft_strlen(here));*/
			/*while (!cmds || !cmds->here)
				cmds = cmds->next;
			cmds->file = fd;
			cmds = cmds->next;*/
	}
	/*int r = 0;
	while (gdata->heredoc[r])
	{
		printf("HERES: %s\n", gdata->heredoc[r]);
		r++;
	}*/
}
