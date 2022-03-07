/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:11:27 by goliano-          #+#    #+#             */
/*   Updated: 2022/03/07 10:44:34 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token_error(int pt, int t, int nt)
{
	if ((pt == 3 && t == 0) || (pt == 1 && t == 0) ||\
		   	(pt == 2 && t == 0) || (pt == 4 && t == 0)\
		   	|| (pt == 3 && t == 1 && nt == 0))
		write(1, "syntax error near unexpected token '|'\n", 40);
	else if ((pt == 3 && t == 1) || (pt == 2 && t == 0) || (pt == 1 && t == 2))
		write(1, "syntax error near unexpected token 'newline'\n", 46);
	else if (pt == 4 && t == 2 && nt == 0)
		write(1, "syntax error near unexpected token '>|'\n", 41);
	else if ((pt == 3 && t == 2) || (pt == 4 && t == 2))
		write(1, "syntax error near unexpected token '>'\n", 40);
	else if ((pt == 4 && t == 1) || (pt == 3 && t == 3) || (pt == 2 && t == 1))
		write(1, "syntax error near unexpected token '<'\n", 40);
	else if (pt == 0 && t == 0)
		write(1, "syntax error near unexpected token '||'\n", 41);
	else if (pt == 4 && t == 4)
		write(1, "syntax error near unexpected token '>>'\n", 40);
	else
		write(1, "syntax error near unexpected token '<<'\n", 40);
}

void	no_cmds_handler(char *s)
{
	int	prev_token;
	int	token;
	int	next_token;
	int	n_tokens;
	int	i;

	i = 0;
	n_tokens = get_n_tokens(s);
	prev_token = ft_get_token(s, &i);
	if (n_tokens == 1 && prev_token == 0)
		return ((void)(write(1, "syntax error near unexpected token '|'\n", 40)));
	if (n_tokens == 1)
		return ((void)(write(1, "syntax error near unexpected token 'newline'\n", 46)));
	while (s[++i])
	{
		token = ft_get_token(s, &i);
		if (token != -1)
		{
			i++;
			next_token = ft_get_token(s, &i);
			print_token_error(prev_token, token, next_token);
			break ;
		}
	}
}
