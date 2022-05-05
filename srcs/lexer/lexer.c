/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:58:58 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/05 15:43:20 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//int ft_count_spec_tokens(int *arr, int len)
//{
//	int	count;
//	int	aux;
//	
//	count = 0; aux = 0;
//	while (aux < len)
		//	{
//		if (arr[aux] == 3 || arr[aux] == 4)
//			count++;
//		aux++;
//	}
//	return (count);
//}

/*char	*remove_char_from_string(char *s, char c)
{
	int		i;
	int		l;
	char	*new_str;

	i = -1;
	l = 0;
	while(s[++i])
	{
		if (s[i] != c)
			l++;
	}
	new_str = ft_calloc(sizeof(char), (l + 1));
	if (!new_str)
		return (0);
	i = -1;
	l = -1;
	while (s[++i])
	{
		if (s[i] != c)
			new_str[++l] = s[i];
	}
	free(s);
	return (new_str);
}*/

void	init_gdata(char *s, t_gdata *gdata)
{
	gdata->n_commands = get_n_commands(s);
	gdata->aux_n_commands = gdata->n_commands;
	gdata->n_tokens = get_n_tokens(s);
	gdata->handle_next = 0;
}

void	lexer(char *s, t_gdata *gdata)
{
	init_gdata(s, gdata);
	s = ft_strtrim(s, " ");
	if (exists_error(s, gdata))
		return ;
	handle_input(s, gdata);
	if (gdata->data_error > 0)
		return ; //gestion de comillas abiertas lexer
	init_tokens(s, gdata);
}
