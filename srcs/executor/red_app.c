/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_app.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:38:39 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/31 15:31:02 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_red_or_app(t_dlist *aux)
{
	int	tkn;
	int	it_is;

	it_is = 0;
	tkn = ((t_token_data *)aux->content)->token;
	if (tkn == 2 || tkn == 4)
		it_is = 1;
	return (it_is);
}

static void	multiple_reds(t_dlist *aux)
{
	char	**files;
	int		i;
	char	*cmd;

	i = 0;
	cmd = ft_strtrim((((t_token_data *)aux->content)->str), " ");
	cmd = ft_strtrim(cmd, " ");
	if (!cmd)
		return ;
	files = ft_split(cmd, ' ');
	while (files[i])
	{
		handle_file_no_create(files[i]);
		i++;
	}
	i = 0;
	while (files[i])
	{
		free(files[i]);
		i++;
	}
}

t_dlist *do_red_or_app(t_dlist *aux, t_gdata *gdata)
{
	char	*cmd;
	int	tkn;
	int	is_red;

	aux = aux->next;
	tkn = ((t_token_data *)aux->content)->token;
	while (tkn == 2 || tkn == 4)
	{
		is_red = 0;
		if (tkn == 2) //red
			is_red = 1;
		aux = aux->next;
		cmd = ft_strtrim((((t_token_data *)aux->content)->str), " ");
		cmd = ft_strtrim(cmd, " ");
		printf("ABRO: %s\n", cmd);
		if (is_red)
			gdata->fd[1] = handle_file_create(cmd, 0);
		else
			gdata->fd[1] = handle_file_create(cmd, 1);
		aux = aux->next;
		if (!aux)
			return (aux);
		tkn = ((t_token_data *)aux->content)->token;
		if (tkn >= 5)
			multiple_reds(aux);
	}
	return (aux->next);
}
