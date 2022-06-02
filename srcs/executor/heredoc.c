/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:32:42 by goliano-          #+#    #+#             */
/*   Updated: 2022/06/01 16:41:52 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*int	is_heredoc(t_dlist *aux)
{
	int	tkn;
	int	it_is;

	it_is = 0;
	tkn = ((t_token_data *)aux->content)->token;
	if (tkn == 3)
		it_is = 1;
	return (it_is);
}*/

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

/*int	next_is_heredoc(t_dlist *aux)
{
	int	tkn;
	int	it_is;

	aux = aux->next;
	it_is = 0;
	if (!aux)
		return (it_is);
	tkn = ((t_token_data *)aux->content)->token;
	if (tkn == 3)
		it_is = 1;
	return (it_is);
}*/

static void	here_cmd_exec(int *end, char *cmd, t_gdata *gdata)
{
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	handle_path(cmd, gdata->envp);
}

/*t_dlist	*do_here_cmd(t_dlist *lst, t_gdata *gdata)
{
	//t_dlist	*aux;
	char	*cmd;
	int		end[2];
	pid_t	p;
	int	status;

	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	printf("CMD: %s\n", cmd);
	//aux = lst;
	lst = lst->next;
	lst = do_heredoc(lst, gdata);
	pipe(end);
	write(end[1], gdata->heredoc, ft_strlen(gdata->heredoc));
	p = fork();
	status = 0;
	if (p < 0)
		write(2, "error\n", 6);
	if (p == 0)
		here_cmd_exec(end, cmd, gdata);
	close(end[0]);
	close(end[1]);
	waitpid(p, &status, 0);
	if (WEXITSTATUS(status))
	{
		write(2, "WEXIT1\n", 7);
	}
	//char *word = malloc(sizeof(char) + 9000);
	//read(end[0], word, ft_strlen(gdata->heredoc));
	//write(2, word, ft_strlen(word));
	//printf("WORD: %s\n", word);
	//handle_cmd3(end[0], end, cmd, gdata->envp);
	return (lst);
}*/

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

void	do_here_cmd(t_dlist *lst, t_gdata *gdata)
{
	char	*cmd;
	char	*here;
	int		end[2];
	pid_t	p;
	int	status;

	lst = lst->prev;
	lst = lst->prev;
	if (!lst)
		return ;
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	printf("CMD: %s\n", cmd);
	lst = lst->next;
	lst = lst->next;
	here = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	fill_heredoc(gdata, here);
	pipe(end);
	write(end[1], gdata->heredoc, ft_strlen(gdata->heredoc));
	p = fork();
	status = 0;
	if (p < 0)
		write(2, "error\n", 6);
	if (p == 0)
		here_cmd_exec(end, cmd, gdata);
	close(end[0]);
	close(end[1]);
	waitpid(p, &status, 0);
	if (WEXITSTATUS(status))
	{
		write(2, "WEXIT1\n", 7);
	}
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

int	need_exec(t_dlist *lst)
{
	int	tkn;
	int	need_it;

	lst = lst->next;
	need_it = 1;
	while (lst)
	{
		tkn = ((t_token_data *)lst->content)->token;
		if (tkn != 3)
			need_it = 0;
		lst = lst->next;
	}
	return (need_it);
}

void	do_heredocs(t_dlist *lst, t_gdata *gdata)
{
	char	*cmd;
	//int		checker;
	//t_dlist	*aux;
	//int	next_type;

	//aux = lst->next;
	lst = go_heredoc(lst);
	cmd = ft_strtrim((((t_token_data *)lst->content)->str), " ");
	if (has_quotes(cmd))
		cmd = cpy_str_no_quotes(cmd);
	printf("BUSCO: %s\n", cmd);
	if (is_last_heredoc(lst) && need_exec(lst))
	{
		printf("ULTIMO\n");
		do_here_cmd(lst, gdata);
	}
	else
	{
		printf("NOCMD\n");
		fill_heredoc(gdata, cmd);
	}
	/*next_type = get_next_type(aux);
	if (next_type == 3 || next_type == -1)
		return (aux->next);
	free(cmd);
	return (aux);*/
}
