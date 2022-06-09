/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:33:00 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/09 14:02:47 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exists_heredoc(t_dlist *lst)
{
	int	tkn;
	int	exists;

	exists = 0;
	while (lst && !exists)
	{
		
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
			exists = 1;
		lst = lst->next;
	}
	return (exists);
}

int	is_last_heredoc(t_dlist *lst)
{
	int	count;
	int	tkn;
	int	it_is;

	count = 0;
	it_is = 0;
	lst = lst->prev;
	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
			count++;
		lst = lst->next;
	}
	if (count == 1)
		it_is = 1;
	return (it_is);
}

int	need_exec(t_dlist *lst)
{
	int	tkn;
	int	prev;
	int	next;
	char *cmd;

	lst = lst->prev;
	if (!lst->prev)
		return (0);
	lst = lst->prev;
	if (!lst->prev)
		return (1);
	lst = iterate_red_app(lst);
	prev = get_prev_type(lst);
	next = get_next_type(lst);
	tkn = ((t_token_data *)lst->content)->token;
	cmd = ((t_token_data *)lst->content)->str;
	printf("CMD0: %s\n", cmd);
	printf("TKN0: %d\n", tkn);
	printf("PREV: %d\n", prev);
	if (prev == 3)
		lst = lst->next;
	if (prev == 1)
		lst = iterate_ind(lst);
	tkn = ((t_token_data *)lst->content)->token;
	if (tkn >= 5)
		return (1);
	cmd = ((t_token_data *)lst->content)->str;
	printf("CMD1: %s\n", cmd);
	printf("TKN1: %d\n", tkn);
	printf("LLEGO\n");
	return (0);
}

void	fill_heredoc(t_gdata *gdata, char *cmd)
{
	char	*line;
	int	i;
	int	checker;

	line = readline("> ");
	gdata->heredoc = line;
	i = 0;
	while (line)
	{
		checker = 0;
		if (!ft_strncmp(line, cmd, ft_strlen(cmd)))
			checker++;
		if (!ft_strncmp(line, cmd, ft_strlen(line)))
			checker++;
		if (checker == 2)
			break ;
		if (i != 0)
			gdata->heredoc = ft_strjoinnl(gdata->heredoc, line);
		line = readline("> ");
		i++;
	}
	gdata->heredoc = append_nl(gdata->heredoc);
}
