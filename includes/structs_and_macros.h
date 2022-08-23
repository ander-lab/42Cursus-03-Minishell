/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_and_macros.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:53:28 by goliano-          #+#    #+#             */
/*   Updated: 2022/08/24 01:00:33 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_AND_MACROS_H
# define STRUCTS_AND_MACROS_H

# include "./libft/libft.h"

/* ************************************************************************** */
/*  								MACROS									  */
/* ************************************************************************** */

/*
** LEXER
*/

typedef enum s_token_type
{
	PIPE,
	INDIRECTION,
	REDIRECTION,
	HERE_DOC,
	APPEND,
	FILE_NAME,
	ARGUMENT,
}	t_token_type;

/* ************************************************************************** */
/*  								STRUCTS									  */
/* ************************************************************************** */

/*
** ENV
*/

typedef struct s_env_line
{
	char	*key;
	char	*value;
}	t_env_line;

typedef struct s_env
{
	t_list	*env_lst;
	char	**envp;
	char	*home;
	char	*pwd;
	char	*old_pwd;
	int		shlvl;
}	t_env;

/*typedef struct s_cmds_data
{
	char				*cmd;
	int					ind;
	int					red;
} t_cmds;
*/

/*
** PROMPT
*/

typedef struct s_data
{
	char	*prompt;
	int		n_commands;
	int		commands;
	int		aux_n_commands;
	int		n_tokens;
	int		err;
	int		inf_err;
	char	**cmds;
	int		last_token;
	int		handle_next;
	t_dlist	*glob_lst;
	t_cmds	*cmds_lst;
	t_env	*env;
	int		fd_pipe;
	int		n_pipes;
	char	**heredoc;
	int		**fd;
	int		type;
	int		r;
}	t_gdata;

typedef struct s_quotes
{
	int		fq;
	size_t	c;
	int		qw;
}	t_quotes;

/*
** LEXER
*/

typedef struct s_token_data
{
	int		token;
	char	*str;
}	t_token_data;

typedef struct g_struc
{
	int	proc;
}	t_glob;

t_glob	s_glob; //TODO-> CAMBIAR S_ POR G_

#endif
