/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:56:10 by goliano-          #+#    #+#             */
/*   Updated: 2022/09/12 14:15:34 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cmd_conditions(t_dlist *lst, int tkn, char **cmd, int *i)
{
	int	next;
	int	prev;

	prev = get_prev_type(lst);
	next = get_next_type(lst);
	if ((prev < 1 || prev > 4) && (next < 1 || next > 4) && tkn > 4)
	{
		if (*i == 0)
			free(*cmd);
		*cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
		*i = 1;
	}
	else if ((prev < 1 || prev > 4) && (next > 1 || next < 4) && (tkn > 4))
	{
		if (*i == 0)
			free(*cmd);
		*cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	}
	*i = 0;
}

char	*get_cmd(t_dlist *lst)
{
	char	*cmd;
	int		tkn;
	int		i;

	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	tkn = (((t_token_data *)lst->content)->token);
	i = 0;
	while (lst && tkn != 0)
	{
		cmd_conditions(lst, tkn, &cmd, &i);
		lst = lst->next;
		if (lst)
			tkn = (((t_token_data *)lst->content)->token);
	}
	return (cmd);
}
