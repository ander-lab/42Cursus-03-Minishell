/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:02:26 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/15 12:28:47 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_quote(char c)
{
	int	quotes;

	quotes = 0;
	if (c == '\"')
		quotes = 1;
	if (c == '\'')
		quotes = 1;
	return (quotes);
}

int is_in_quotes(int quotes)
{
	int is_in_quotes;

	if (quotes)
		is_in_quotes = 0;
	else
		is_in_quotes = 1;
	return (is_in_quotes);
}

char	*get_until_token(int prev_l, int l, char *str)
{
	char	*word;
	int quotes;
	int	i;

	quotes = 0;
	word = malloc(sizeof(char) * (l - prev_l + 1));
	if (!word)
		return (0);
	i = 0;
	while (prev_l < l)
	{
		//if (is_quote(str[prev_l]))
		//		quotes = is_in_quotes(quotes);
		//if (quotes == 0 && str[prev_l] != '<' && str[prev_l] != '>')
		word[i] = str[prev_l];
		i++;
		prev_l++;
	}
	word[i] = '\0';
	return (word);
}

void	handle_input(char *s, t_gdata *g_data/*, t_token_data *cmd_table*/)
{
	int	prev_l;
	int	l;
	int	token;
	char	*word;
	int	quotes;

	l = 0;
	prev_l = 0;
	quotes = 0;
	while (s[l])
	{
		if (is_quote(s[l]))
				quotes = is_in_quotes(quotes);
		if (s[l + 1])
			token = ft_give_token(s[l], s[l + 1], &l);
		else
			token = ft_give_token(s[l], 0, NULL);
		if (token != -1 && quotes == 0)
		{
			word = get_until_token(prev_l, l, s);
			printf("word: %s\n", word);
			g_data->n_commands--;
			prev_l = l + 1;
			//if (s[l] == '<' || s[l + 1] == '>')
			//	prev_l++;
		}
		l++;
	}
	if (g_data->n_commands == 1)
	{
		word = get_until_token(prev_l, l, s);
		printf("word: %s\n", word);
	}
}

int	get_n_commands(char *s)
{
	int	i;
	int	nc;
	int	token;
	int	quotes;

	i = 0;
	nc = 1;
	token = 0;
	quotes = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
				quotes= is_in_quotes(quotes);
		if (s[i + 1])
			token = ft_give_token(s[i], s[i + 1], &i);
		else
			token = ft_give_token(s[i], 0, NULL);
		if (token != -1 && quotes == 0)
			nc++;
		i++;
	}
	return (nc);
}