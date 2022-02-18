/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:02:26 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/18 18:11:43 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_ind_red(char *s)
{
	char	*aux;
	int		i;
	int		quotes;
	int		x;

	i = -1;
	x = -1;
	aux = ft_calloc(sizeof(char), (ft_strlen(s) + 1));
	if (!aux)
		return (s);
	quotes = 0;
	while (s[++i])
	{
		if (is_quote(s[i]) == 1)
			quotes = is_in_quotes(quotes, 1);
		if (is_quote(s[i]) == 2)
			quotes = is_in_quotes(quotes, 2);
		if (quotes == 0 && s[i] != '<' && s[i] != '>')
			aux[++x] = s[i];
		if (quotes == 1 || quotes == 2)
			aux[++x] = s[i];
		//if (quotes == 2)
		//	aux[++x] = s[i];
	}
	free(s);
	return (aux);
}

char	*get_until_token(int prev_l, int l, char *str)
{
	char	*word;
	int		i;

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

void	handle_input(char *s, t_gdata *g_data)
{
	int		prev_l;
	int		l;
	int		token;
	char	*word;
	int		quotes;
	int		i;

	l = -1;
	prev_l = 0;
	quotes = 0;
	i = 0;
	g_data->cmds = ft_calloc(sizeof(char *), (g_data->n_commands + 1));
	if (!g_data->cmds)
		return ;
	while (s[++l])
	{
		if (is_quote(s[l]) == 1)
			quotes = is_in_quotes(quotes, 1);
		if (is_quote(s[l]) == 2)
			quotes = is_in_quotes(quotes, 2);
		token = ft_get_token(s, l);
		if (token != -1 && quotes == 0)
		{
			g_data->n_commands--;
			word = get_until_token(prev_l, l, s);
			if (word[0])
			{
				g_data->cmds[i] = word;
				i++;
			}
			prev_l = l + 1;
		}
	}
	if ((g_data->n_commands == 0 || g_data->n_commands == 1) && !ends_with_token(s))
	{
		word = get_until_token(prev_l, l, s);
		g_data->cmds[i] = word;
	}
	g_data->data_error = quotes;
}

int	is_cmd_between_tokens(char *s, int idx)
{
	int	token;
	int	cmd_exists;

	token = 0;
	cmd_exists = 0;
	while (s[++idx])
	{
		token = ft_get_token(s, idx);
		if (token != -1)
			return (cmd_exists);
		if (token == -1 && s[idx] != ' ')
			cmd_exists = 1;
	}
	return (cmd_exists);
}

int	get_n_commands(char *s)
{
	int	i;
	int	nc;
	int	token;
	int	quotes;

	i = -1;
	nc = 1;
	token = 0;
	quotes = 0;
	while (s[++i])
	{
		if (is_quote(s[i]) == 1)
			quotes = is_in_quotes(quotes, 1);
		if (is_quote(s[i]) == 2)
			quotes = is_in_quotes(quotes, 2);
		token = ft_get_token(s, i);
		if (token != -1 && quotes == 0 && is_cmd_between_tokens(s, i))
			nc++;
	}
	if (starts_with_token(s))
		nc--;
	return (nc);
}
