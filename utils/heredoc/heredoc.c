/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:33:00 by goliano-          #+#    #+#             */
/*   Updated: 2022/09/12 16:57:11 by goliano-         ###   ########.fr       */
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

static	int	check_heredoc(char *line, char *cmd)
{
	int	checker;

	checker = 0;
	if (!ft_strncmp(line, cmd, ft_strlen(cmd)))
		checker++;
	if (!ft_strncmp(line, cmd, ft_strlen(line)))
		checker++;
	return (checker);
}

char	*fill_heredoc(char *cmd)
{
	char	*line;
	char	*here;
	int		i;
	int		checker;

	line = readline("> ");
	here = line;
	i = 0;
	while (line)
	{
		checker = check_heredoc(line, cmd);
		if (checker == 2)
		{
			if (i == 0)
				here = 0;
			break ;
		}
		if (i != 0)
			here = ft_strjoinnl(here, line);
		line = readline("> ");
		signal(SIGINT, SIG_IGN);
		i++;
	}
	return (append_nl(here));
}
