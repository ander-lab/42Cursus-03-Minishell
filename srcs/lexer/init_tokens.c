/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:53:22 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/20 14:41:10 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_token(char *s, int *raw_tokens, int i, int l)
{
//	printf("LLEGA: %c\n", s[i]);
	if (s[i] == ' ')
		raw_tokens[l] = -3;
	else
		raw_tokens[l] = -1;
}

/*static	void	check_no_spaces(int token, char *s, int i)
{
	int	next_token;

	i++;
	next_token = ft_get_token(s, &i);
	printf("TOKEN: %d\n", token);
	printf("NEXT_TOKEN: %d\n", next_token);
}*/

static int	put_tokens_on_arr(char *s, int *raw_tokens)
{
	int	i;
	int	l;
	int	token;
	int	quotes;

	i = -1;
	l = 0;
	quotes = 0;
	while (s[++i])
	{
		quotes = quote_type(quotes, s, i);
		token = ft_get_token(s, &i);
	//	printf("-----------------------\n");
	//	printf("CHAR: %c\n", s[i]);
	//	printf("TOKENS: %d\n", token);
		if (token != -1 && quotes == 0 /*&& is_cmd_between_tokens(s, i)*/)
		{
			raw_tokens[l] = token;
	//		check_no_spaces(token, s, i);
			int r = i;
			//if (is_cmd_hide(s, ++r, token))
			if (is_cmd_hide(s, ++i, token))
				raw_tokens[++l] = -2;
			i = r;
		}
		else
			write_token(s, raw_tokens, i, l);
		//printf("ESCRIBO[%d]: %d\n", l, raw_tokens[l]);
		l++;
	}
	//printf("RAW_LEN: %d\n", l);
	return (l);
}

/*static void	ft_printdlst(t_dlist *token_lst)
{
	while (token_lst)
	{
		printf("token  %i char * %s\n", ((t_token_data *)token_lst->content)->token, \
				((t_token_data *)token_lst->content)->str);
		token_lst = token_lst->next;
	}
}*/

void	init_tokens(char *s, t_gdata *gdata)
{
	int				raw_len;
	int				*raw_tokens;
	t_dlist			*token_lst;
	t_token_data	*token_data;
	int				*clean_tkns;

	token_data = ft_calloc(sizeof(t_token_data), 1);
	raw_tokens = ft_calloc(ft_strlen(s) + 2, sizeof(int));
	token_lst = NULL;
	raw_len = put_tokens_on_arr(s, raw_tokens);
	/*int j = 0;
	while (j < raw_len)
	{
		printf("CRAW: %d\n", raw_tokens[j]);
		j++;
	}*/
	clean_tkns = clean_tokens(raw_tokens, raw_len, \
			gdata->n_commands + gdata->n_tokens);
	/*int x = 0;
	while (x < gdata->n_commands + gdata->n_tokens)
	{
		printf("CLEAN: %d\n", clean_tkns[x]);
		x++;
	}*/
	ft_insert_data_lst(&token_lst, token_data, clean_tkns, \
			gdata->n_commands + gdata->n_tokens);
	ft_convert_matrix(gdata->cmds, token_lst);
	clean_lst_tokens(token_lst);
	//printf("\n------------------------------\n");
	gdata->cmds_list = token_lst;
	//ft_printdlst(token_lst);
}
