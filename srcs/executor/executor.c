/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:17:54 by goliano-          #+#    #+#             */
/*   Updated: 2022/05/26 15:58:25 by goliano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_next_type(t_dlist *lst)
{
	t_dlist	*aux;
	int		tkn;
	int		type;

	aux = lst;
	aux = aux->next;
	if (!aux)
		return (-1);
	tkn = ((t_token_data *)aux->content)->token;
	type = tkn;
	if (tkn == 0)			//viene commando (pipe)
		type = 0;
	else if (tkn == 2)		//viene redireccion (>)
		type = 1;
	else if (tkn == 4)		//viene append (>>)
		type = 2;
	return (type);
}

int	get_prev_type(t_dlist *lst)
{
	t_dlist	*aux;	
	int		tkn;

	aux = lst;
	aux = aux->prev;
	if (!aux)
		return (-2);
	tkn = ((t_token_data *)aux->content)->token;
	return (tkn);
}

static void	handle_executor(t_gdata *gdata, t_dlist *aux, int *end, char *cmd)
{
	int	next_type;
	int	prev_type;

	next_type = get_next_type(aux);
	prev_type = get_prev_type(aux);
	if (next_type == 1 || prev_type == 2) //red
		gdata->fd[1] = open_next_file(aux, 0);
	else if (next_type == 2) //append
		gdata->fd[1] = open_next_file(aux, 1); 
	if (next_type == 0)	//pipe
		handle_cmd1(gdata->fd[0], end, cmd, gdata->envp);
	else if (next_type == 1 || next_type == 2 || prev_type == 2)	//redirección
		handle_cmd2(gdata->fd[1], end, cmd, gdata->envp);
	else if (next_type == -1)		//un cmd
		handle_cmd3(0, end, cmd, gdata->envp);
	//else if (next_type == 2)	//append
	//	handle_cmd2(gdata->fd[1], end, cmd, gdata->envp);
	gdata->commands--;
}

static int	is_token_file(t_dlist *aux)
{
	int	is_file;
	int	tkn;

	is_file = 0;
	tkn = ((t_token_data *)aux->content)->token;
	if (is_file_token(tkn) && tkn != 3)
		is_file = 1;
	return (is_file);
}

int	is_heredoc(t_dlist *aux)
{
	int	tkn;
	int	it_is;

	it_is = 0;
	tkn = ((t_token_data *)aux->content)->token;
	if (tkn == 3)
		it_is = 1;
	return (it_is);
}

int		length_str_no_quotes(char *cmd)
{
	int	l;
	int	i;
	int	quote_type;

	i = 0;
	l = 0;
	quote_type = 0;
	while (cmd[i])
	{
		if (quote_type == is_quote(cmd[i]))
			quote_type = 0;
		if (!quote_type && is_quote(cmd[i]))
			quote_type = is_quote(cmd[i]);
		if (is_quote(cmd[i]) != quote_type)
			l++;
		else if (!is_quote(cmd[i]))
			l++;
		i++;
	}
	return (l);
}

char	*cpy_str_no_quotes(char *cmd)
{
	int		l;
	int		i;
	int		quote_type;
	char	*word;

	i = 0;
	l = 0;
	quote_type = 0;
	word = malloc(sizeof(char *) + (length_str_no_quotes(cmd) + 1));
	if (!word)
		return (0);
	while (cmd[i])
	{
		if (quote_type == is_quote(cmd[i]))
			quote_type = 0;
		if (!quote_type && is_quote(cmd[i]))
			quote_type = is_quote(cmd[i]);
		if (is_quote(cmd[i]) != quote_type)
			word[l++] = cmd[i];
		else if (!is_quote(cmd[i]))
			word[l++] = cmd[i];
		i++;
	}
	word[l] = '\0';
	free(cmd);
	return (word);
}

void	do_heredoc(t_dlist *lst)
{
	char	*cmd;
	char	*line;
	int		checker;
	t_dlist	*aux;

	aux = lst;
	aux = lst->next;
	cmd = ft_strtrim((((t_token_data *)aux->content)->str), " ");
	if (has_quotes(cmd))
		cmd = cpy_str_no_quotes(cmd);
	line = readline("> ");
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
		line = readline("> ");
	}
}

/*void	executor(t_gdata *gdata)
{
	t_dlist	*aux;
	char	*cmd;
	int		file;
	int		end[2];

	aux = gdata->cmds_list;
	file = 0;
	pipe(end);
	while (aux && gdata->commands > 0)
	{
		cmd = ft_strtrim((((t_token_data *)aux->content)->str), " ");
		cmd = ft_strtrim(cmd, " ");
		if (file && cmd)
			gdata->fd[0] = handle_file_no_create(cmd);
		if (is_token_file(aux))
			file = 1;
		if (is_heredoc(aux))
		{
			do_heredoc(aux);
			aux = aux->next;
		}
		if (!file && cmd)
			handle_executor(gdata, aux, end, cmd);
		if (cmd && file > 0)
			file = 0;
		aux = aux->next;
	}
}*/

char	*cpy_until_space(char *cmd)
{
	int		i;
	int		l;
	char	*word;

	i = 0;
	l = 0;
	while (is_quote(cmd[i]))
		i++;
	while (cmd[i])
	{
		if (cmd[i] == ' ' || is_quote(cmd[i]))
			break ;
		i++;
		l++;
	}
	word = malloc(sizeof(char *) + (l + 1));
	if (!word)
		return (0);
	i = 0;
	l = 0;
	while (is_quote(cmd[i]))
		i++;
	while (cmd[i] && !is_quote(cmd[i]) && cmd[i] != ' ')
	{
		word[l] = cmd[i];
		i++;
		l++;
	}
	word[i] = '\0';
	return (word);
}

int		is_builtin(char *cmd)
{
	int		it_is;
	char	*builtin;

	it_is = 0;
	builtin = cpy_until_space(cmd);
	if (!ft_strncmp("echo", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("echo", builtin, ft_strlen("echo")))
		it_is = 1;
	else if (!ft_strncmp("cd", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("cd", builtin, ft_strlen("cd")))
		it_is = 1;
	else if (!ft_strncmp("pwd", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("pwd", builtin, ft_strlen("pwd")))
		it_is = 1;
	else if (!ft_strncmp("export", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("export", builtin, ft_strlen("export")))
		it_is = 1;
	else if (!ft_strncmp("unset", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("unset", builtin, ft_strlen("unset")))
		it_is = 1;
	else if (!ft_strncmp("env", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("env", builtin, ft_strlen("env")))
		it_is = 1;
	else if (!ft_strncmp("exit", builtin, ft_strlen(builtin)) \
			&& !ft_strncmp("exit", builtin, ft_strlen("exit")))
		it_is = 1;
	free(builtin);
	return (it_is);
}

void	execute_builtin(t_gdata *gdata, char *cmd)
{
	char	*builtin;

	builtin = cpy_until_space(cmd);
	if (!ft_strncmp("echo", builtin, ft_strlen("echo")))
		ft_echo(ft_split(cmd, ' '));
	else if (!ft_strncmp("env", builtin, ft_strlen("env")))
		ft_env(gdata->envp, ft_split(cmd, ' '));
	else if (!ft_strncmp("exit", builtin, ft_strlen("exit")))
		ft_exit(ft_split(cmd, ' '));
	else if (!ft_strncmp("pwd", builtin, ft_strlen("pwd")))
		ft_pwd();
}

void	executor(t_gdata *gdata)
{
	t_dlist	*aux;
	char	*cmd;
	int		file;
	int		end[2];
	int		ind;
	int		tkn;

	aux = gdata->cmds_list;
	file = 0;
	ind = 0;
	tkn = 0;
	pipe(end);
	while (aux && gdata->commands > 0)
	{
		cmd = ft_strtrim((((t_token_data *)aux->content)->str), " ");
		cmd = ft_strtrim(cmd, " ");
		tkn = ((t_token_data *)aux->content)->token;
		if (tkn == 1)
			ind = 1;
		if (file && cmd && ind)
		{
			gdata->fd[0] = handle_file_no_create(cmd);
			ind = 0;
		}
		if (is_token_file(aux) && tkn != 2)
			file = 1;
		if (is_heredoc(aux))
		{
			do_heredoc(aux);
			aux = aux->next;
			//handle_executor(gdata, aux, end, cmd);
		}
		if (is_builtin(cmd))
			execute_builtin(gdata, cmd);
		//return ;
		else if (!file && cmd)
			handle_executor(gdata, aux, end, cmd);
		if (cmd && file > 0)
			file = 0;
		aux = aux->next;
	}
}
