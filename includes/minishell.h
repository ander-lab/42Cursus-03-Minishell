/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goliano- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:33:34 by goliano-          #+#    #+#             */
/*   Updated: 2022/02/08 10:46:37 by ajimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
# endif

typedef struct g_data
{
	char	*prompt;
	char	**envp;
}t_gdata;

void	init_prompt(t_gdata *g_data, char **envp);

//char	*get_next_line(int fd);
//size_t	ft_strlen(char const *str);
//char	*ft_strjoin(char const *str1, char const *s2);
//char	**ft_split(char const *s, char c);
//char	*ft_strjoin(char const *s1, char const *s2);

#endif
