/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_and_macros.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 09:39:19 by ajimenez          #+#    #+#             */
/*   Updated: 2022/02/15 11:06:02 by ajimenez         ###   ########.fr       */
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

/*
** PROMPT
*/

typedef struct s_data
{
	char	*prompt;
	char	**envp;
	int	n_commands;
} t_gdata;

/*
** LEXER
*/

typedef struct s_token_data
{
	int		token;
	char	*str;
}	t_token_data;

#endif
