/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:11:27 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/31 09:46:45 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_token_error(int pt, int t, int nt)
{
	if ((pt == 3 && t == 0) || (pt == 1 && t == 0) || \
			(pt == 4 && t == 0) || (pt == 3 && t == 1 && nt == 0))
		write(1, "syntax error near unexpected token '|'\n", 40);
	else if ((pt == 3 && t == 1) || (pt == 2 && t == 0) \
			|| (pt == 1 && t == 2) || (pt == 2 && t == 0))
		write(1, "syntax error near unexpected token 'newline'\n", 46);
	else if (pt == 4 && t == 2 && nt == 0)
		write(1, "syntax error near unexpected token '>|'\n", 41);
	else if ((pt == 3 && t == 2) || (pt == 4 && t == 2))
		write(1, "syntax error near unexpected token '>'\n", 40);
	else if ((pt == 3 && t == 3 && nt == 1) || (pt == 3 && t == 3 && nt == -1))
		write(1, "syntax error near unexpected token '<<'\n", 40);
	else if (pt == 3 && t == 3 && nt == 3)
		write(1, "syntax error near unexpected token '<<<'\n", 41);
	else if ((pt == 4 && t == 1) || (pt == 3 && t == 3 \
				&& (nt == 0 || nt == -2)) || (pt == 2 && t == 1))
		write(1, "syntax error near unexpected token '<'\n", 40);
	else if (pt == 0 && t == 0)
		write(1, "syntax error near unexpected token '||'\n", 41);
	else if (pt == 4 && t == 4)
		write(1, "syntax error near unexpected token '>>'\n", 40);
}

static int	prev_handler(int n_tokens, int prev_token, int hp)
{
	if (n_tokens == 1 && prev_token == 0)
		return (write(1, "syntax error near unexpected token '|'\n", 40));
	if (n_tokens == 1 || hp == 1)
		return (write(1, "syntax error near unexpected token 'newline'\n", 46));
	return (0);
}

static void	error_handler(char *s, int hp)
{
	int	prev_token;
	int	token;
	int	next_token;
	int	n_tokens;
	int	i;

	i = 0;
	n_tokens = get_n_tokens(s);
	prev_token = ft_get_token(s, &i);
	if (prev_handler(n_tokens, prev_token, hp) > 0)
		return ;
	next_token = -2;
	while (s[++i])
	{
		token = ft_get_token(s, &i);
		if (token != -1)
		{
			i++;
			if (s[i])
				next_token = ft_get_token(s, &i);
			print_token_error(prev_token, token, next_token);
			break ;
		}
	}
}

int	exists_error(char *s, t_gdata *gdata)
{
	int	exists;

	exists = 1;
	if (gdata->n_commands == 0)
		error_handler(s, 0);
	else if (ends_with_token(s))
		error_handler(s, 1);
	else
		exists = 0;
	return (exists);
}
