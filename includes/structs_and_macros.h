/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_and_macros.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 09:39:19 by ajimenez          #+#    #+#             */
/*   Updated: 2022/07/26 12:53:12 by ajimenez         ###   ########.fr       */
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
} t_token_type;

/* ************************************************************************** */
/*  								STRUCTS									  */
/* ************************************************************************** */

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
	char	**envp;
	int		n_commands;	// comandos y redirecciones
	int		commands;	// comandos solo (pipes)
	int		aux_n_commands;
	int		n_tokens;
	int		err;
	int		inf_err;
	char	**cmds;
	int		last_token;
	int		handle_next;
	t_dlist	*glob_lst;
	t_cmds	*cmds_lst;
	int		fd_pipe;
	int		n_pipes;
	char	**heredoc;
} t_gdata;

/*
** LEXER
*/

typedef struct s_token_data
{
	int		token;
	char	*str;
}	t_token_data;


/*
** ENV
*/

typedef struct s_env_line
{
	char	*key;
	char	*value;
} t_env_line;


typedef struct s_env
{
	t_list *env_lst;
	char	 **envp;
	char	 *home;
	char	 *pwd;
	char	 *old_pwd;
	//TODO poner strings mas usados en la struct ej. home, pwd, oldpwd... y hacer una funcion que vaya actualizandolo cada vez que pasa por el executor
}	t_env;

#endif
