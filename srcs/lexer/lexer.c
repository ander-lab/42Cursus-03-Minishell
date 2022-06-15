/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:58:58 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/15 14:51:56 by goliano-         ###   ########.fr       */
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

void ft_printdlst(t_dlist *token_lst)
{
	while (token_lst)
	{
		//printf("----hell");
		printf("token  %i char * %s\n", ((t_token_data *)token_lst->content)->token,
			((t_token_data *)token_lst->content)->str);
		//token_data = token_lst->content;
		//printf(" token 2= %i\n", token_data->token);
		token_lst = token_lst->next;
	}
}

void	init_gdata(char *s, t_gdata *gdata)
{
	gdata->n_commands = get_n_commands(s);
	gdata->aux_n_commands = gdata->n_commands;
	gdata->n_tokens = get_n_tokens(s);
	gdata->handle_next = 0;
	gdata->commands = command_count(s);
	gdata->fd[0] = 0;
	gdata->fd[1] = 1;
}

/*void	free_gdata(t_gdata *gdata)
{
	int	i;

	i = 0;
	while (gdata->cmds[i])
	{
		free(gdata->cmds[i]);
		i++;
	}
}*/

void	lexer(char *s, t_gdata *gdata)
{
	init_gdata(s, gdata);
	s = ft_strtrim(s, " ");
	if (exists_error(s, gdata))
		return ;
	handle_input(s, gdata);
	if (gdata->err)
		return ; //gestion de comillas abiertas lexer
	//ft_putmatrix(gdata->cmds, get_n_commands(s));
	init_tokens(s, gdata);
	//parser(gdata);
	//if (gdata->err)
	//	return ; //gestion de comillas abiertas lexer
	executor(gdata);
	//free(gdata);
}
