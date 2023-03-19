/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellie <vellie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:37:41 by vellie            #+#    #+#             */
/*   Updated: 2022/03/08 14:37:05 by vellie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "lib_utils/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

int					g_error;

typedef struct s_err
{
	int			is_heredoc;
	int			how_quit;
	int			is_quit;
}				t_err;

typedef struct s_red
{
	int				type;
	char			*file;
	char			*un_tok;
	struct s_red	*next;
}					t_red;

typedef struct s_var
{
	char			*v_key;
	char			*v_val;
	char			*str;
	struct s_var	*next;
}					t_var;

typedef struct s_env
{
	char			*key;
	char			*value;

	struct s_env	*next;
}					t_env;

typedef struct s_info
{
	int					err;
	char				**envp;
	int					size;
	int					exit;

	t_env				*env;
	t_var				*var;
	struct s_command	*commands;
}						t_info;

typedef struct s_command
{
	char				**argvstr;
	char				*cmd_name;
	char				*full_path;
	int					flag;
	int					fd_in;
	int					fd_out;
	int					fd[2];
	int					n_args;
	t_info				*info;
	t_red				*red;
	int					redin;
	int					redout;
	struct s_command	*next;
	int					tmp;
	int					flag_red;
}				t_command;

typedef struct s_move
{
	t_env	*head;
	t_env	*tail;
	size_t	size;
}			t_move;

void		heredoc_change(void);
void		main_change(void);
void		command_change(void);
void		quit_hand(int sig);
void		main_sig(int sig);
void		heredoc_sig(int sig);
void		command_sig(int sig);
void		perenos(int sig);
void		do_exit(int sig);
t_command	*ft_newcmd(t_info *info);
int			ft_lstsize(t_command *head);
void		ft_lstadd_back(t_command **lst, t_command *newel);
void		ft_lstclear(t_command **lst);
int			info_initialization(int argc, char **argv,
				char **envp, t_info **info);
void		clear_red_data(t_command *cmd);
void		clear_cmd_data(t_command *cmd);
void		info_reinit(t_info *info);
void		cmd_pipe_run(t_command *cmd);
void		cmd_fd_change(t_command *cmd);
int			pipes(t_command *cmd);
int			change_stdout(t_command *cmd);
int			change_stdin(t_command *cmd);
void		execute_cmd(t_command *cmd);
void		cmd_run(t_command *cmd);
int			sizeofcmd(t_command *head);
void		do_cmd(t_info *info);
int			err(char *msg);
int			redirect_type1(t_red *red, t_command *cmd);
int			redirect_type2(t_red *red, t_command *cmd);
int			redirect_type3(t_red *red, t_command *cmd);
int			redirect_type4(t_command *cmd);
int			ft_cmpstr(const char *s1, const char *s2);
int			unexpected_token(t_red *red);
int			redirects(t_command *cmd);
char		*find_key(t_info info, char *str);
void		add_cd_env(t_info *info, char *home, char *pwd);
void		change_dir(t_info *info, char *old_dir);
void		cd_single(t_info *info);
void		cd_move(t_info *info);
void		cd_home(t_info *info);
int			b_cd(t_info *info);
int			print_env(t_info *pars);
int			clear_builtin(t_command *cmd);
void		do_clear_built(t_command *cmd);
int			is_built(char *str);
int			builtins(t_command *com);
int			b_unset(t_command *cmd);
void		unset_elem(t_command *cmd, char *arg);
int			delete_env_var(t_info *info, char *key);
int			b_pwd(void);
void		move_var_type2(t_command *cmd, char *arg, int i);
void		move_var_type1(t_command *cmd, char *arg, int i);
void		add_to_envp(t_info *info, char *arg);
int			var_parsing(t_command *cmd, char *arg, int *i);
int			b_export(t_command *cmd);
int			b_echo(t_info *pars);
int			argument_edit(t_command *cmd);
int			redfile_add(t_command *cmd, char *str, int *i);
int			argument_add(t_command *cmd, char *str, int i);
int			pair_symbol(char *str, char sym, int *i);
int			argument_parser(char *str, t_command *cmd, int *y);
void		end_start_dollar(char *arg, int *start, int *end);
int			dollar_arg(char sym);
int			no_dollar(char *arg);
char		*refactor_string(t_command *cmd, char *str, int start, int end);
int			dollar_parser(t_command *cmd, int num);
void		first_part(char **res, char *str, int start, int *i);
void		second_part(char **res, char *d_val, int dollar_len, int *i);
void		third_part(char **res, char *str, int end, int *i);
t_env		*env_last(t_env *env);
t_env		*env_create(char *key, char *value);
int			envcmp(const char *s1, const char *s2);
int			env_paste(t_env **head, t_env *newel, t_info *info);
void		envp_parser(t_info *info, char **envp);
int			env_parser(t_info *info, char **args);
int			add_elem_env(t_info *info, char *str);
char		*is_in_env(t_info *info, char *source);
int			ft_path_strcmp(char *s1, char *s2);
char		*find_path(char **arg);
char		*free_all(char ***str, char *res);
void		free_char(char **str);
char		*find_full_path(char *env_path, char *command);
int			parser(char *str, t_command *cmd);
int			argument_search(char **str, t_command *cmd);
void		redirect_search(char **str, t_command *cmd);
int			ft_first_sym(int ch);
int			ft_allowed_sym(int ch);
int			in_env(t_info *info, char *source);
int			env_change(t_info *info, char *key, char *new_val);
char		*find_value(t_var **head, char *key);
char		**allocate_memory(t_command *cmd);
int			delete_memory(t_command *cmd, int num);
void		reverse_quo_num(int *first, int *quotes, char sym);
int			env_var_pattern(t_command *cmd, char *arg);
int			file_pattern(char *str);
int			command_pattern(t_command *cmd, char *arg);
int			find_patterns(t_command *cmd);
int			check_comand(char *str, t_command *com);
int			quotes_data(char sym, int quotes1, int quotes2, int first);
int			end_start_quotes(char *arg, int *start, int *end);
int			refactor_quotes(t_command *cmd, int num, int start, int end);
int			quotes_parser(t_command *cmd, int num);
t_red		*return_point(t_red *red);
t_red		*create_red(void);
int			red_add(t_red **head, t_red *newel, t_command *command);
int			return_redtype(char sym, int max);
void		redirect_parser(char **str, t_command *cmd);
t_var		*create_var(char *str, char *key, char *val);
void		add_var(t_command *cmd, t_var *newel);
int			change_var(t_command *cmd, char *key, char *value);
int			in_var(t_var *head, char *key);
int			delete_var(t_var **head, char *key);
void		do_mom(t_info *info, int fd);
void		do_child(t_info *info);
void		command_process(t_info *info);
void		rl_replace_line(const char *text, int clear_undo);
int			return_qu(int *end, int i, char sym);
#endif