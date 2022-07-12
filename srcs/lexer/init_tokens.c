/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:53:22 by goliano-          #+#    #+#             */
/*   Updated: 2022/07/11 13:41:20 by goliano-         ###   ########.fr       */
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
	int	r;

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
			r = i;
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

int	last_infile(t_dlist *lst)
{
	char *file;
	int	fd;

	fd = -1;
	if (lst->prev)
		lst = lst->prev;
	file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	if (file)
		fd = handle_file_no_create(file);
	return (fd);
}

int	last_red(t_dlist *lst, int red)
{
	char 	*file;
	int		fd;
	int		prev;

	fd = -1;
	if (!red)
		return (fd);
	prev = get_prev_type(lst);
	file = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	if (prev == 2)
		fd = handle_file_create(file, 0);
	else if (prev == 4)
		fd = handle_file_create(file, 1);
	return (fd);
}

t_cmds	*fill_cmds(char *cmd, int ind, int red)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (0);
	cmds->content = cmd;
	cmds->ind = ind;
	cmds->red = red;
	cmds->next = NULL;
	return (cmds);
}

int	exist_red(t_dlist *lst)
{
	int	prev;
	int	exists;

	exists = 0;
	prev = get_prev_type(lst);
	if (prev == 2 || prev == 4)
		exists = 1;
	return (exists);
	/*char *cmd2 = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	printf("CMD RED: %s\n", cmd2);
	prev = get_prev_type(lst);
	while (lst && prev != 0)
	{
		tkn = ((t_token_data *)lst->content)->token;
		lst = lst->prev;
	}*/
	/*char *cmd2 = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	printf("CMD2 RED: %s\n", cmd2);
	if (lst->prev)
		lst = lst->prev;
	prev = get_prev_type(lst);
	if (prev == 2 || prev == 4)
		exists = 1;*/
}

void	init_cmds_lst(t_gdata *gdata)
{
	t_cmds	*cmds;
	t_dlist	*glob_lst;
	char	*cmd;
	int		ind;
	int		red;

	cmds = NULL;
	glob_lst = gdata->glob_lst;
	while (glob_lst)
	{
		ind = -1;
		red = -1;
		glob_lst = iterate_ind(glob_lst);
		cmd = ft_strtrim((((t_token_data *)glob_lst->content)->str), " ");
		ind = last_infile(glob_lst);
		if (!cmd)
		{
			glob_lst = iterate_red_app(glob_lst);
		}
		else
		{
			glob_lst = iterate_red_app_next(glob_lst);
		}
		//if (cmd)
		//	glob_lst = glob_lst->next;
			//ft_dlstadd_back2(&cmds, ft_dlstnew2(cmd, ind));
		red = last_red(glob_lst, exist_red(glob_lst));
		//if (red > 2)
		//	glob_lst = glob_lst->prev;
		/*char *cmd2 = ft_strtrim((((t_token_data *)glob_lst->content)->str), " ");
		printf("CMD1: %s\n", cmd);
		printf("CMD2: %s\n", cmd2);
		printf("IND: %d\n", ind);
		printf("RED: %d\n", red);
		*/
		if (cmd)
			ft_dlstadd_back2(&cmds, fill_cmds(cmd, ind, red));
		glob_lst = glob_lst->next;
		if (glob_lst && glob_lst->next)
			glob_lst = glob_lst->next;
	}
	/*while (cmds)
	{
		printf("CMD: %s\n", (char *)cmds->content);
		printf("IND: %d\n", cmds->ind);
		printf("RED: %d\n", cmds->red);
		cmds = cmds->next;
	}*/
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
