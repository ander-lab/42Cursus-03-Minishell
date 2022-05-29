/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:51:41 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/26 11:59:23 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_file_no_create(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("File: ");
		return (-1);
	}
	return (fd);
}

int	handle_file_create(char *file, int type)
{
	int	fd;

	if (type)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("File");
		return (-1);
	}
	return (fd);
}

int	open_next_file(t_dlist *lst, int type)
{
	t_dlist	*aux;
	char	*cmd;
	int		tkn;

	aux = lst;
	tkn = (((t_token_data *)aux->content)->token);
	cmd = (((t_token_data *)aux->content)->str);
	if (tkn == 5)
		return (handle_file_create(ft_strtrim(cmd, " "), type));
	aux = aux->next;
	if (!aux)
		return (-1);
	aux = aux->next;
	if (!aux)
		return (-1);
	cmd = (((t_token_data *)aux->content)->str);
	return (handle_file_create(ft_strtrim(cmd, " "), type));
}
