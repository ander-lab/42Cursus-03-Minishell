/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:32:42 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/01 16:41:52 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_heredoc(t_dlist *aux)
{
	int	tkn;
	int	it_is;

	it_is = 0;
	tkn = ((t_token_data *)aux->content)->token;
	if (tkn == 3)
		it_is = 1;
	return (it_is);
}

t_dlist	*do_heredoc(t_dlist *lst, t_gdata *gdata)
{
	char	*cmd;
	char	*line;
	int		checker;
	t_dlist	*aux;
	int	next_type;

	aux = lst->next;
	cmd = ft_strtrim((((t_token_data *)aux->content)->str), " ");
	if (has_quotes(cmd))
		cmd = cpy_str_no_quotes(cmd);
	line = readline("> ");
	gdata->heredoc = line;
	while (line)
	{
		checker = 0;
		printf("%s\n", line);
		if (!ft_strncmp(line, cmd, ft_strlen(cmd)))
			checker++;
		if (!ft_strncmp(line, cmd, ft_strlen(line)))
			checker++;
		if (checker == 2)
			break ;
		gdata->heredoc = ft_strjoinnl(gdata->heredoc, line);
		line = readline("> ");
	}
	next_type = get_next_type(aux);
	if (next_type == 3 || next_type == -1)
		return (aux->next);
	free(cmd);
	return (aux);
}
