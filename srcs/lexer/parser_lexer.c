/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:02:26 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/16 13:37:55 by goliano-         ###   ########.fr       */
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
		quotes = 2;
	return (quotes);
}

int is_in_quotes(int quotes, int tquotes)
{
	int is_in_quotes;

	is_in_quotes = 0;
	if (quotes == 0)
		is_in_quotes = tquotes;
	else if (quotes == tquotes)
		is_in_quotes = 0;
	else
		is_in_quotes = quotes;
	return (is_in_quotes);
}

char	*remove_ind_red(char *s)
{
	char	*aux;
	int		i;
	int		quotes;
	int		x;

	i = 0;
	x = -1;
	aux = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!aux)
		return (s);
	quotes = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
			quotes = is_in_quotes(quotes, 1);
		if (is_quote(s[i]) == 2)
			quotes = is_in_quotes(quotes, 2);
		if (quotes == 0 && s[i] != '<' && s[i] != '>')
			aux[++x] = s[i];
		if (quotes == 1)
			aux[++x] = s[i];
		i++;
	}
	aux[++x] = '\0';
	free(s);
	return (aux);
}

char	*get_until_token(int prev_l, int l, char *str)
{
	char	*word;
	int	i;

	word = malloc(sizeof(char) * (l - prev_l + 1));
	if (!word)
		return (0);
	i = 0;
	while (prev_l < l)
	{
		word[i] = str[prev_l];
		i++;
		prev_l++;
	}
	word[i] = '\0';
	word = remove_ind_red(word);
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
			quotes = is_in_quotes(quotes, 1);
		else if (is_quote(s[l]) == 2)
			quotes = is_in_quotes(quotes, 2);
		if (s[l + 1])
			token = ft_give_token(s[l], s[l + 1], &l);
		else
			token = ft_give_token(s[l], 0, NULL);
		if (token != -1 && quotes == 0)
		{
			word = get_until_token(prev_l, l, s);
			//if (!word[0])
			//	free(word);
			g_data->n_commands--;
			printf("WORD1: %s\n", word);
			prev_l = l + 1;
		}
		l++;
	}
	if (g_data->n_commands == 1)
		word = get_until_token(prev_l, l, s);
	printf("WORD2: %s\n", word);
}

int	starts_with_token(char *s)
{
	int	starts;
	int	token;
	int	i;

	i = 0;
	starts = 0;
	while (s[i])
	{
		if (s[i + 1])
			token = ft_give_token(s[i], s[i + 1], &i);
		else
			token = ft_give_token(s[i], 0, NULL);
		if ((i == 0 || i == 1) && token > -1)
			starts = 1;
		i++;
	}
	return (starts);
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
		if (is_quote(s[i]) == 1)
			quotes = is_in_quotes(quotes, 1);
		if (is_quote(s[i]) == 2)
			quotes = is_in_quotes(quotes, 2);
		if (s[i + 1])
			token = ft_give_token(s[i], s[i + 1], &i);
		else
			token = ft_give_token(s[i], 0, NULL);
		if (token != -1 && quotes == 0)
			nc++;
		i++;
	}
	if (starts_with_token(s))
		nc--;
	return (nc);
}
