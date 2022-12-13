/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:24:47 by minsukan          #+#    #+#             */
/*   Updated: 2022/11/09 17:17:41 by yujelee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* headers for allowed functions */
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <curses.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/errno.h>
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>

# include "./symbols.h"
# include "./structs.h"

# define SHELL	"minihell"
# define C_BLUE "\033[34m"
# define C_NRML "\033[0m"

t_info		*g_info;

/*token_tree*/
t_token		*and_or(t_symbol *symbol);
t_token		*brace_group(t_symbol *symbol);
t_token		*make_token(t_symbol *symbol);
t_token		*make_parse_tree(t_symbol *symbol);
t_token		*pipeline(t_symbol *symbol);
t_symbol	*skip_brace(t_symbol *symbol);

/*check_cmd.c*/
char		*get_cmd_path(char *cmd, char *path);
int			is_cmd(char	*str);

/* delete_quote.c */
void		delete_quote(t_symbol *symbol);

/*execute.c*/
void		execute_tree(t_token *tree);

/*expand_env_double_quote.c*/
char		*expand_env_quote_case(char *str);

/*expand_env_utils.c*/
int			cut_temp(char **temp, char *str);
char		*cut_str(char **str);
char		*ft_join(char **str);
int			count_pair(char *str);
char		*get_value(char *str, int *idx);
char		*new_str(char *str, char *key, int *idx);
void		skip_quote(char *str, int *idx, int flag);
void		backup_space_symbol(t_symbol *symbol);
t_symbol	*update_symbol(t_symbol *symbol, t_symbol *new);

/*expand_env.c*/
t_symbol	*expand_env(t_symbol *symbol);

/* expand_filename.c */
void		expand_filename(t_symbol *symbol);

/*manage_env.c*/
int			get_env_len(char *env);
void		parse_env(char **env);
char		*get_env(char *key);
char		**ft_env_split(char *env);

/*manage_envlst.c*/
t_envlst	*ft_envlst_new(char *key, char *value);
t_envlst	*get_envlst(char *key);
void		ft_envlst_add_back(t_envlst *new);
void		set_envlst(char *key, char *value);

/*manage_error.c*/
void		print_error(char *msg1, char *msg2, char *msg3, int type);
void		allocat_error(void);
int			error_msg(char *str);
void		execute_error(char *cmd_path, char **cmd_arr, char **env);
int			open_file_error(char *file);

/*manage_info.c*/
void		init_info(char **env);
void		set_exit_code(int code);

/*manage_mem.c*/
void		split_free(char **str);
void		free_symbol(t_symbol *symbols);
void		free_symbols(t_symbol *symbols);
void		free_tree(t_token *tree);

/*manage_signal.c*/
void		set_child_signal(void);
void		block_signal(void);
void		set_signal(void);

/*manage_symbol.c*/
void		add_back_symbol(t_symbol **head, t_symbol *new);
t_symbol	*get_last_symbol(t_symbol *symbol);
t_symbol	*make_symbol_lst(char **temp);
t_symbol	*new_symbol(char *str);

/*parse_line.c*/
t_token		*parse_line(char *str);

/*replace_space.c*/
void		is_space(char *str);
char		*double_quote(char *str);
char		*single_quote(char *str);
void		replace_white_space(char *str);

/*preprocess_line.c*/
char		**preprocess_line(char *str);
char		*replace_op(char *line);

/* replace_wild_card.c */
void		replace_back_wild_card(char **str);
void		replace_wild_card(char *str);

/*symbolize.c*/
void		symbolizing(t_symbol *symbol_lst);
int			classify_op(char *str);

/*validate.c*/
int			validate(t_symbol *symbol_lst);
int			syntax_error_token(char *str);
char		*get_origin_op(int type);

/*validate_utils.c*/
int			lbrace_case(t_symbol *symbol_lst);
int			rbrace_case(t_symbol *symbol_lst);
int			pipe_andif_orif_case(t_symbol *symbol_lst);
int			direction_case(t_symbol *symbol_lst);
int			check_first_type(int type);

/* functions for built_in */
t_cd		*ft_init_cd_info(int pipe_cnt, char *arg);
void		ft_cd(char **path, int pipe_cnt);
void		ft_check_rv(t_cd *info);
void		ft_cd_home(int pipe_cnt);
void		ft_update_oldpwd(char *old_pwd);
void		ft_update_pwd(char *pwd);
void		ft_unset(char **arg, int pipe_cnt);
void		ft_pwd(char **arg, int pipe_cnt);
void		ft_export(char **arg, int pipe_cnt);
void		ft_pipe_export(char **arg);
void		ft_echo(char **arg, int pipe_cnt);
void		ft_exit(char **arg, int pipe_cnt);
void		ft_env(char **arg, int pipe_cnt);

/* execute_pipe_line.c */
void		execute_pipe_line(t_symbol *symbol);
int			execute_built_in(char **cmd_arr, int pipe_cnt);

/* execute_pipe_line_utils.c */
int			is_built_in(char **cmd_arr);
char		**make_cmd_arr(t_symbol *symbol);
int			count_until_pipe(t_symbol *symbol);
int			get_pipe_cnt(t_symbol *symbol);
void		wait_process(pid_t *pid, int pipe_cnt, int stdin_backup);

/* execute_pipe_line_io.c */
int			dup_redirection(t_symbol *symbol, int stdin_backup, int i);
int			dup_out_redirection(t_symbol *symbol, int type_rid);
int			dup_in_redirection(t_symbol *symbol, int type_rid,
				int stdin_backup, int i);
int			open_file(char *file, int redirection_type);
int			read_here_doc(char *limiter, int stdin_backup, char *heredoc_tmp);

/* execute_pipe_line_io_utils.c */
int			task_here_doc(t_symbol *symbol, int *fd, int stdin_backup, int i);
int			count_after_rid(t_symbol *symbol);
int			len_cmp(int a, int b);
void		dup_parant_pipe(int *fd_pipe, int stdout_backup);
void		dup_child_pipe(int *fd_pipe, int flag, int pipe_cnt, int i);

/* execute_single_commend.c */
int			execute_single_command(t_symbol *symbol, \
			int pipe_cnt, int stdin_backup);

/* make_env.c */
char		**make_env(void);

/*fork_heredoc.c*/
int			fork_heredoc(char *limiter, int stdin_backup, char *heredoc_tmp);

#endif
