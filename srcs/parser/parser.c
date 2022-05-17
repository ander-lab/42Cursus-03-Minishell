/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:17:42 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/17 12:22:26 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*static int parser_handler(int tkn, char *cmd, int type)
{
	int	error;

	error = 0;
	// tipo 0, empieza en ind, red, h_d, app y luego viene archivo
	if (type == 0 && tkn != 5)
		error = 1;
	// dos tokens seguidos
	if (type == 1 && (tkn != 5 || tkn != 6))
		error = 1;
	//printf("TKN: %d\n", tkn);
	printf("CMD: %s\n", cmd);
	//printf("ERROR: %d\n", error);
	return (error);
}*/

/*int check_consecutive_tokens()
{

}*/

int parser(t_gdata *gdata)
{
	int		tkn;
	int		is_ftkn;
	int		is_tkn;
	t_dlist	*aux;

	is_ftkn = 0;
	is_tkn = 0;
	aux = gdata->cmds_list;
	while (aux && !gdata->err)
	{
		tkn = ((t_token_data *)aux->content)->token;
		if (is_file_token(tkn))
			is_ftkn = 1;
		if (is_ftkn || tkn == 0)
			is_tkn = 1;
		if (is_ftkn || is_tkn)
		{
			aux = aux->next;
			tkn = ((t_token_data *)aux->content)->token;
		}
		if (is_tkn && tkn >= 0 && tkn <= 4)
		{
			write(1, "syntax error near unexpected token 'newline'\n", 46);
			gdata->err = 1;
		}
	//	parser_handler(tkn, cmd, 0);
		//parser_handler(tkn, cmd, 1);
		is_ftkn = 0;
		is_tkn = 0;
		aux = aux->next;
	}
	return (1);
}
