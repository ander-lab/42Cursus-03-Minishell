#include "../../includes/minishell.h"

int	exists_heredoc(t_dlist *lst)
{
	int	tkn;
	int	exists;

	exists = 0;
	while (lst && !exists)
	{
		
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
			exists = 1;
		lst = lst->next;
	}
	return (exists);
}

int	is_last_heredoc(t_dlist *lst)
{
	int	count;
	int	tkn;
	int	it_is;

	count = 0;
	it_is = 0;
	lst = lst->prev;
	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn == 3)
			count++;
		lst = lst->next;
	}
	if (count == 1)
		it_is = 1;
	return (it_is);
}

t_dlist	*go_heredoc(t_dlist *lst)
{
	int	tkn;

	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		lst = lst->next;
		if (tkn == 3)
			break;
	}
	return (lst);
}

int	need_exec(t_dlist *lst)
{
	t_dlist *aux;
	int	tkn;
	char *cmd;

	aux = go_to_pipe(lst);
	if (aux)
	{
		tkn = ((t_token_data *)aux->content)->token;
		tkn = ((t_token_data *)aux->content)->token;
		if (tkn >= 5)
			return (1);
	}
	lst = lst->prev;
	lst = lst->prev;
	if (!lst)
		return (0);
	int prev = get_prev_type(lst);
	while (prev == 2 || prev == 4)
	{
		lst = lst->prev;
		lst = lst->prev;
		prev = get_prev_type(lst);
	}
	prev = get_prev_type(lst);
	if (prev == 3)
		lst = lst->next;
	else if (prev == 1)
	{
		lst = lst->next;
		int next = get_next_type(lst);
		while (next == 1)
		{
			lst = lst->next;
			lst = lst->next;
			next = get_next_type(lst);
		}
	}
	if (tkn >= 5)
		return (1);
	return (0);
}

void	fill_heredoc(t_gdata *gdata, char *cmd)
{
	char	*line;
	int	i;
	int	checker;

	line = readline("> ");
	gdata->heredoc = line;
	i = 0;
	while (line)
	{
		checker = 0;
		printf("%s\n", line);
		if (!ft_strncmp(line, cmd, ft_strlen(cmd)))
			checker++;
		if (!ft_strncmp(line, cmd, ft_strlen(line)))
			checker++;
		if (checker == 2)
			break ;
		if (i != 0)
			gdata->heredoc = ft_strjoinnl(gdata->heredoc, line);
		line = readline("> ");
		i++;
	}
	gdata->heredoc = append_nl(gdata->heredoc);
}
