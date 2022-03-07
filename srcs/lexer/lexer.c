/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 11:18:10 by ajimenez          #+#    #+#             */
/*   Updated: 2022/03/07 11:11:26 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	put_tokens_on_arr(char *s, int *raw_tokens)
{
	int	i;
	int	l;
	int	token;
	int	quotes;

	i = 0;
	l = 0;
	quotes = 0;
	//s = remove_char_from_string(s, ' ');
	//printf("S: %s\n", s);
	while (s[i])
	{
		quotes = quote_type(quotes, s, i);
		token = ft_get_token(s, &i);
		if (token != -1 && quotes == 0 && is_cmd_between_tokens(s, i))
		{
			raw_tokens[l] = token;
			if (is_cmd_hide(s, ++i, token))
			{
				l++;
				raw_tokens[l] = -2;
			}
		}
		else
		{
			if (s[i] == ' ')
				raw_tokens[l] = -3;
			else
				raw_tokens[l] = token;
		}
		i++;
		l++;
	}
	return (l);
}

void	init_gdata(char *s, t_gdata *gdata)
{
	gdata->n_commands = get_n_commands(s);
	gdata->aux_n_commands = gdata->n_commands;
	gdata->n_tokens = get_n_tokens(s);
	gdata->handle_next = 0;
}

void lexer(char *s, t_gdata *gdata)
{
	int		*raw_tokens;
	int		raw_len;
	int 	*clean_tkns;
	t_dlist			*token_lst;
	t_token_data	*token_data;

	token_data = ft_calloc(sizeof(t_token_data), 1);
	raw_tokens = ft_calloc(ft_strlen(s) + 2, sizeof(int));
	token_lst = NULL;
	init_gdata(s, gdata);
	s = ft_strtrim(s, " ");
	if (gdata->n_commands == 0)
		return (no_cmds_handler(s));
	handle_input(s, gdata);
	if (gdata->data_error > 0)
		return ; //gestion de comillas abiertas lexer
	raw_len = put_tokens_on_arr(s, raw_tokens);
	clean_tkns = clean_tokens(raw_tokens, raw_len, gdata->n_commands + gdata->n_tokens);
	ft_insert_data_lst(&token_lst, token_data, clean_tkns, gdata->n_commands + gdata->n_tokens);
	ft_convert_matrix(gdata->cmds, token_lst);
	clean_lst_tokens(token_lst);
	printf("\n-----------------------\n");
	ft_printdlst(token_lst);
}
