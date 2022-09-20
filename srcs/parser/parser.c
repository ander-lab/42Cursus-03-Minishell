/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:17:42 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/20 17:48:31 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_parser_error(int i, t_dlist *aux)
{
	int	tkn;
	int	next_type;
	int	err;

	err = 0;
	tkn = ((t_token_data *)aux->content)->token;
	next_type = get_next_type(aux);
	if (i == 0 && tkn == 0)
	{
		write(1, "syntax error near unexpected token '|'\n", 40);
		err = 1;
	}
	if (next_type >= 0 && next_type <= 4 && tkn >= 0 && tkn <= 4)
	{
		write(1, "syntax error near unexpected token 'newline'\n", 46);
		err = 1;
	}
	return (err);
}

void	parser(t_gdata *gdata)
{
	t_dlist	*aux;
	int		i;

	aux = gdata->glob_lst;
	i = 0;
	while (aux && !gdata->err)
	{
		if (check_parser_error(i, aux))
			gdata->err = 1;
		i++;
		aux = aux->next;
	}
}
