/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:53:22 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/20 17:45:55 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_token(char *s, int *raw_tokens, int i, int l)
{
	if (s[i] == ' ')
		raw_tokens[l] = -3;
	else
		raw_tokens[l] = -1;
}

//TODO -> NORMINETTE LINES
static int	put_tokens_on_arr(char *s, int *raw_tokens)
{
	int	i;
	int	l;
	int	token;
	int	quotes;
	int	r;

	i = -1;
	l = 0;
	quotes = 0;
	while (s[++i])
	{
		quotes = quote_type(quotes, s, i);
		token = ft_get_token(s, &i);
		if (token != -1 && quotes == 0)
		{
			raw_tokens[l] = token;
			r = i;
			if (is_cmd_hide(s, ++i, token))
				raw_tokens[++l] = -2;
			i = r;
		}
		else
			write_token(s, raw_tokens, i, l);
		l++;
	}
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

static t_cmds	*fill_cmds(char *cmd, int ind, int red, int here)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (0);
	cmds->content = cmd;
	cmds->ind = ind;
	cmds->red = red;
	cmds->here = here;
	cmds->exp = 0;
	cmds->next = NULL;
	return (cmds);
}

//TODO -> NORMINETTE VAR
void	init_cmds_lst(t_gdata *gdata)
{
	t_cmds	*cmds;
	t_dlist	*glob_lst;
	char	*cmd;
	int		ind;
	int		red;
	int		here;

	cmds = NULL;
	glob_lst = gdata->glob_lst;
	while (glob_lst)
	{
		ind = get_ind(glob_lst);
		red = get_red(glob_lst);
		cmd = get_cmd(glob_lst);
		here = need_exec_here(glob_lst);
		ft_dlstadd_back2(&cmds, fill_cmds(cmd, ind, red, here));
		glob_lst = iter_to_pipe(glob_lst);
	}
	gdata->cmds_lst = cmds;
}

void	init_tokens(char *s, t_gdata *gdata)
{
	int				raw_len;
	int				*raw_tokens;
	t_dlist			*token_lst;
	t_token_data	*token_data;
	int				*clean_tkns;

	token_data = ft_calloc(sizeof(t_token_data), 1);
	raw_tokens = ft_calloc(sizeof(int), ft_strlen(s) + 1);
	token_lst = NULL;
	raw_len = put_tokens_on_arr(s, raw_tokens);
	clean_tkns = clean_tokens(raw_tokens, raw_len, \
			gdata->n_commands + gdata->n_tokens);
	ft_insert_data_lst(&token_lst, token_data, clean_tkns, \
			gdata->n_commands + gdata->n_tokens);
	ft_convert_matrix(gdata->cmds, token_lst);
	clean_lst_tokens(token_lst);
	gdata->glob_lst = token_lst;
	init_cmds_lst(gdata);
	free(raw_tokens);
	free(clean_tkns);
}
