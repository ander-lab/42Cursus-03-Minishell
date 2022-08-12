/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajimenez <ajimenez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:17:40 by ajimenez          #+#    #+#             */
/*   Updated: 2022/08/12 12:11:19 by ajimenez         ###   ########.fr       */
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
# include "structs_and_macros.h"

# define READ_END 0
# define WRITE_END 1

extern void rl_replace_line(const char *c, int x);

void	init_prompt(t_gdata *g_data, char **envp);
void 	lexer(char *s, t_gdata *g_data);

int	*clean_tokens(int *raw, int raw_len, int len);
//int		*clean_tokens(int *raw, int raw_len, int len, int n_commands);

void	clean_lst_tokens(t_dlist *token_lst);
int		ft_give_token(char c1, char c2, int *aux);
char	*get_until_token(int prev_l, int l, char *str);
int		is_escaping(char c);
void	handle_input(char *str, t_gdata *g_data/*, t_token_data *cmd_table*/);
int		get_n_commands(char *s);

/*
 *	srcs/builtins/ft_pwd.c
 */
int		ft_pwd();

/*
 *	srcs/builtins/ft_echo.c
 */
int		ft_echo(char **cmd, int red, t_gdata *gdata);
/*
 *	srcs/builtins/ft_unset.c
 */
int		ft_unset(t_list **env, char **cmd);
/*
 *	srcs/builtins/ft_env.c
 */
//int		ft_env(char **env, char **args);
int 	ft_env(char **args, t_gdata *data);
/*
 *	srcs/builtins/ft_export.c
 */
int	ft_export(t_list **env, char **cmd);
int	check_var_replace(t_list **lst, char *key, char *value);
/*
 *	srcs/builtins/ft_exit.c
 */
int		ft_exit(char **cmd, t_gdata *data);

/*
 *	srcs/builtins/ft_exit.c
 */
int		ft_cd(t_gdata *data, char **cmd);

/*
 *	srcs/builtins/utils.c
 */
char	*safe_getcwd(char *current_cwd);
t_list	*ft_lstnew_struct(void *newcontent, size_t size);
char	*ft_strjoin_token(char const *s1, char const *s2, char token);
void	envp_to_lst(char **envp, t_list **lst_env);
void	ft_lstfree(t_list *lst);
//char	**lst_to_envmtrx(t_list *lst_env, char **envp);
void	lst_to_envmtrx(t_list *lst_env, t_gdata *gdata);
char	*ft_dup_var(t_list **lst, char *key);

/*
 *	srcs/lexer/lexer.c
 */
void	ft_printdlst(t_dlist *token_lst);

/*
 *	srcs/prompt/prompt.c
 */
char	*remove_new_line(char *str);

/*
 *	srcs/executor/executor.c
 */
void	executor(t_gdata *gdata);

/*
 *	srcs/executor/heredoc.c
 */
void	do_heredoc(t_dlist *lst, t_gdata *gdata);

/*
 *	srcs/lexer/spaces.c
 */
int		is_file_token(int t);

/*
 *	srcs/parser/parser.c
 */
void		parser(t_gdata *gdata);
/*
 *	srcs/lexer/init_tokens.c
 */
void	init_tokens(char *s, t_gdata *gdata);

/*
 *	utils/global/count.c
 */
int		command_count(char *s);

/*
 * utils/quotes/quotes.c
 */
int		is_quote(char c);
int		is_in_quotes(int quotes, int tquotes);
int     quote_type(int quotes, char *s, int l);
int		has_quotes(char *s);

/*
 *	utils/files/files.c
 */
int		handle_file_no_create(char *file);
int		handle_file_create(char *file, int type);
int		open_next_file(t_dlist *lst, int type);

/*  
 * utils/tokens/tokens.c
 */
int		ft_get_token(char *s, int *l);
int		ft_give_token(char c1, char c2, int *aux);
int		ends_with_token(char *s);
int		starts_with_token(char *s);
int		get_n_tokens(char *s);

/*
 * utils/str/strings.c
 */
char	*remove_ind_red(char *s);
int		exists_word(char *s);
int		is_cmd_between_tokens(char *s, int idx);
char	*get_until_token(int prev_l, int l, char *str);
int		spaces_or_null(char *s);

/*
 * utils/str/strings2.c
 */
char	*cmd_add_slash(char	*cmd);
char	*cpy_cmd(char *s, int l, int idx);
char	*cpy_cmd2(char *s, int fl, int l);
char	*pretty_hostname(char *str);
char	*add_at_sign(char *str);

/*
 *	utils/str/strings3.c
 */
char	*cpy_str_no_quotes(char *cmd);
char	*cpy_until_space(char *cmd);
char	*append_nl(char *str);

/*
 * utils/chequer/chequer.c
 */
int		needs_split(char *word);
int		get_cmd_length_until_token(char *s, int idx);
int		is_cmd_hide(char *s, int idx, int token);
int		need_cmd_slash(char *cmd);

/*
 * utils/lengths/lengths.c
 */
int		length_from_idx(char *word, int idx);
int		get_cmds_length(t_gdata *g_data);
int		filename_length(char *word);
int		length_str_no_quotes(char *cmd);
int		matrix_length(char **mat);

/*
 *	utils/handler/error_handler.c
 */
int		exists_error(char *s, t_gdata *gdata);

/*
 *	utils/cmd_exec/cmd_exec.c
 */
int		handle_path(char *cmd, char **envp);

/*
 *	utils/forks/forks.c
 */
void	handle_cmd(t_gdata *gdata, t_cmds *cmds_lst);

/*
 * srcs/env/init_env.c
 */

void	init_env(t_gdata *data, char **envp);

/*
 *	srcs/executor/infile.c
 */
int			is_infile(t_dlist *aux);
t_dlist*	do_infile(t_dlist *lst, t_gdata *gdata);
//void		infile_checker(t_dlist *lst, t_gdata *gdata);
void		handle_infile(t_dlist *lst, t_gdata *gdata);

/*
 *	srcs/executor/red_app.c
 */
t_dlist *do_red_or_app(t_dlist *aux);
int		is_red_or_app(t_dlist *aux);

/*
 *	srcs/executor/builtins.c
 */
int		is_builtin(char *cmd);
void	execute_builtin(t_cmds *cmds, t_gdata *gdata, char *cmd);

/*
 *	utils/builtins/echo.c
 */
int	print_cmd_proc(char **cmd, int red, t_gdata *gdata);

/*
 *	srcs/lexer/token_to_list.c
 */
//t_list	*ft_lstnew_struct(void *newcontent, size_t size);
void	ft_insert_data_lst(t_dlist **lst, t_token_data *token_data, int *tokens, int len);
void	ft_convert_matrix(char **words, t_dlist *lst);

/*
 *	utils/heredoc/heredoc.c
 */
char	*fill_heredoc(char *cmd);
int		exists_heredoc(t_dlist *lst);

/*
 *	utils/heredoc/heredoc2.c
 */
t_dlist	*iterate_ind(t_dlist *lst);
t_dlist	*iterate_red_app(t_dlist *lst);
t_dlist	*go_heredoc(t_dlist *lst);

/*
 *	utils/cmds/cmds.c
 */
int	last_infile(t_dlist *lst);
int	last_red(t_dlist *lst, int red);
int	exist_red(t_dlist *lst);
int	get_ind(t_dlist *lst);
int	get_red(t_dlist *lst);

/*
 *	srcs/lexer/cmds_lst.c
 */
char	*get_cmd(t_dlist *lst);
t_dlist	*iter_to_pipe(t_dlist *lst);
t_dlist	*move_to_last_heredoc(t_dlist *lst);
int		exists_heredoc_until_pipe(t_dlist *lst);
int		need_exec_here(t_dlist *lst);

/*
 *	utils/list/list.c
 */
int	get_next_type(t_dlist *lst);
int	get_prev_type(t_dlist *lst);


void ft_printkey(t_list *token_lst);
/*
 *	utils/signals/signals.c
 */
void	sigquit_child(int n);
void	child_signal_handler(int pid);

#endif
