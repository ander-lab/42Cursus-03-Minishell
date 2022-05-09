/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:17:42 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/09 15:12:28 by goliano-         ###   ########.fr       */
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
	char	*cmd;
	int		is_ftkn;
	int		is_tkn;

	is_ftkn = 0;
	is_tkn = 0;
	while (gdata->cmds_list && !gdata->err)
	{
		tkn = ((t_token_data *)gdata->cmds_list->content)->token;
		cmd = ((t_token_data *)gdata->cmds_list->content)->str;
		if (is_file_token(tkn))
			is_ftkn = 1;
		if (is_ftkn || tkn == 0)
			is_tkn = 1;
		if (is_ftkn || is_tkn)
		{
			gdata->cmds_list = gdata->cmds_list->next;
			tkn = ((t_token_data *)gdata->cmds_list->content)->token;
			cmd = ((t_token_data *)gdata->cmds_list->content)->str;
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
		gdata->cmds_list = gdata->cmds_list->next;
	}
	printf("ERROR: %d\n", gdata->err);
	return (1);
}
