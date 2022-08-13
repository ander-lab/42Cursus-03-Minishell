/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:17:54 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/10 13:32:43 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	exists_pipe(t_dlist *lst)
{
	int	exists;
	int	tkn;

	exists = 0;
	while (lst && !exists)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 0)
			exists = 1;
		lst = lst->next;
	}
	return (exists);
}

static int	get_n_pipes(t_dlist *lst)
{
	int	tkn;
	int	pipes;

	pipes = 0;
	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 0)
			pipes++;
		lst = lst->next;
	}
	return (pipes);
}

/*void	init_quote_struct(t_quotes *qs)
{
	qs->fq = 0;
	qs->c = 0;
	qs->qw = 0;
}

void	quotes_handler(char *cmd, t_quotes *qs)
{
	int			i;
	int			qt;

	i = 0;
	init_quote_struct(qs);
	while (cmd[i])
	{
		qt = is_quote(cmd[i]);
		//printf("QT: %d\n", qt);
		//printf("FQ: %d\n", qs.fq);
		if (qt == qs->fq)
			qs->fq = 0;
		else if (qt != 0 && qs->fq != 0)
		{
			qs->qw = qt;
			qs->c++;
		}
		else if (qt > 0 && qs->fq == 0)
			qs->fq = qt;
		i++;
	}
}

size_t	cmd_length(char *cmd)
{
	size_t	l;
	int		i;

	i = 0;
	l = 0;
	while (cmd[i])
	{
		if (!is_quote(cmd[i]))
				l++;
		i++;
	}
	return (l);
}

static int	*append_free(int *index, int new)
{
	int	ind;
	int	*ret;

	ind = 0;
	while (index[ind] != -1)
		ind++;
	ret = (int *)malloc(sizeof(int) * (ind + 2));
	ret[ind + 1] = -1;
	ret[ind] = new;
	while (--ind >= 0)
		ret[ind] = index[ind];
	free(index);
	return (ret);
}

static int	*index_str(int *index, char *order, char limit)
{
	char	limiter;

	index = append_free(index, index[0]);
	index[1]++;
	limiter = '\0';
	while (order[index[0]] && (order[index[0]] != limit || limiter))
	{
		if (order[index[0]] == '\'' || order[index[0]] == '\"')
		{
			if (!limiter)
				limiter = order[index[0]];
			else if (order[index[0]] == limiter)
				limiter = '\0';
		}
		index[0]++;
	}
	index = append_free(index, index[0]);
	while (order[index[0]] && order[index[0]] == limit)
		index[0]++;
	if (!order[index[0]])
		return (index);
	return (index_str(index, order, limit));
}

char	**smart_split(char *order, char limit)
{
	int		*index;
	char	**ret;
	int		ind;
	int		ind2;

	index = (int *)malloc(sizeof(int) * 3);
	index[0] = 0;
	index[1] = 0;
	index[2] = -1;
	order = ft_strtrim(order, " ");
	index = index_str(index, order, limit);
	ret = (char **)malloc(sizeof(char *) * (index[1] + 1));
	ind = 2;
	ind2 = 0;
	while (index[ind] != -1)
	{
		ret[ind2++] = ft_substr(order, index[ind], \
		(index[ind + 1] - index[ind]));
		ind += 2;
	}
	ret[ind2] = NULL;
	free(order);
	free(index);
	return (ret);
}

void	*rewrite_quotes(char *cmd, t_quotes qs)
{
	char	*new;
	int		i;
	int		x;

	//printf("L: %d\n", cmd_length(cmd));
	char **sp = smart_split(cmd, '\"');
	int	r = 0;
	while (sp[r])
	{
		printf("sp[r]: %s\n", sp[r]);
		r++;
	}
	new = ft_calloc(sizeof(char), cmd_length(cmd) + qs.c);
	i = 0;
	x = -1;
	while (cmd[i])
	{
		if (!is_quote(cmd[i]))
			new[++x] = cmd[i];
		else
		{
			if (qs.qw == 1)
				new[++x] = '\"';
			else
				new[++x] = '\'';
		}
		i++;
	}
	printf("CMD: %s\n", cmd);
	printf("qs.c: %zu\n", qs.c);
	printf("qw: %d\n", qs.qw);
	return (cmd);
}

void	handle_exp(t_cmds *cmds)
{
	t_quotes	qs;
	char		*cmd;

	while (cmds)
	{
		cmd = (char *)cmds->content;
		quotes_handler(cmd, &qs);
		cmds->content = rewrite_quotes(cmd, qs);
		cmds = cmds->next;
	}
}
*/

int	strquotes_len(char *cmd)
{
	int	qt;
	int	fq;
	int	i;
	int	l;
	int	lq;

	fq = 0;
	qt = 0;
	i = 0;
	l = 0;
	lq = 0;
	while (cmd[i])
	{
		qt = is_quote(cmd[i]);
		if (qt > 0 && fq == 0)
			fq = qt;
		else if (qt == fq && fq != 0)
			lq = 1;
		else if (qt == fq)
			fq = 0;
		if ((fq != qt || qt == 0) && lq == 0)
			l++;
		lq = 0;
		i++;
	}
	return (l);
}

char	*remove_quotes(char  *cmd)
{
	int		qt;
	int		i;
	int		x;
	int		fq;
	char		*new;

	i = 0;
	fq = 0;
	x = -1;
	new = ft_calloc(sizeof(char), ft_strlen(cmd) + 1);
	if (!new)
		return (0);
	int lq = 0;
	while (cmd[i])
	{
		qt = is_quote(cmd[i]);
		if (qt > 0 && fq == 0)
			fq = qt;
		else if (qt == fq && fq != 0)
			lq = 1;
		else if (qt == fq)
			fq = 0;
		if ((fq != qt || qt == 0) && lq == 0)
			new[++x] = cmd[i];
		lq = 0;
		i++;
	}
	free(cmd);
	return (new);
}

void	check_expansion(t_cmds *cmds)
{
	char	*cmd;
	int	x;
	int	qt;
	int	fq;

	cmd = (char *)cmds->content;
	x = 0;
	fq = 0;
	while (cmd[x])
	{
		qt = is_quote(cmd[x]);
		if (qt > 0 && fq == 0)
			fq = qt;
		else if (qt == fq)
			fq = 0;
		if (cmd[x] == '$' && (fq == 1 || fq == 0))
			cmds->exp = 1;
		x++;
	}
}

void	cmds_iteration(t_cmds *cmds)
{
	char	*cmd;

	while (cmds)
	{
		cmd = (char *)cmds->content;
		check_expansion(cmds);
		cmds->content = remove_quotes(cmd);
		cmds = cmds->next;
	}
}

void	executor(t_gdata *gdata)
{
	t_dlist	*lst;
	t_cmds	*cmds;

	//TODO -> Duplicar envp 
	//TODO -> Duplicar env keys
	//TODO -> LLamar a env to matrix y lst to env
	cmds = gdata->cmds_lst;
	cmds_iteration(cmds);
	//handle_exp(cmds);
	lst = gdata->glob_lst;
	gdata->n_pipes = get_n_pipes(lst);
	do_heredoc(lst, gdata);
	handle_infile(lst, gdata);
	if (gdata->inf_err && !exists_pipe(lst))
		return ;
	handle_cmd(gdata, cmds);
//	while (cmds)
//	{
//		printf("CMD: %s\n", (char *)cmds->content);
//		printf("IND: %d\n", cmds->ind);
//		printf("RED: %d\n", cmds->red);
//		cmds = cmds->next;
//	}
}
