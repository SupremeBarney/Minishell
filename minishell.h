/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:31:14 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/25 15:42:59 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE
# define _POSIX_C_SOURCE 200809L
# include <stdlib.h>
# include <stdio.h>
# include "libftprintf/ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_cmd
{
	char			**args;
	char			*input;
	char			*output;
	char			*heredoc;
	char			*output_append;
	struct s_cmd	*next;
}	t_cmd;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	HEREDOC,
	REDIR_OUT,
	REDIR_OUT_APPEND,
}	t_token_type;

typedef struct s_environment_variable
{
	char							*name;
	char							*value;
	struct s_environment_variable	*next;
}	t_env;

typedef struct s_token
{
	char			*token;
	t_token_type	token_type;
	int				had_quotes;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
	char	*read_line;
}	t_shell;

typedef struct s_parse
{
	int	i;
	int	token_start;
	int	quote_flag;
}	t_parse;

extern volatile sig_atomic_t	g_signal;

void			handle_sigint_heredoc(int sig);
void			handle_sigint(int sig);
void			setup_signals(void);
void			setup_heredoc_signal(void);
char			*strjoin_free(char *s1, char *s2);
char			*read_heredoc(char *delimiter, t_shell shell);
int				nb_of_tokens(t_token *token);
void			init_cmd(t_cmd *cmd);
int				pipe_token(t_cmd **cur_cmd, t_token **cur_token, int *i);
void			redir_in_token(t_token **cur_token, t_cmd *cur_cmd);
int				heredoc_token(t_cmd **cmd, t_token **cur_token,
					t_cmd *cur_cmd, t_shell shell);
void			redir_out_token(t_token **cur_token, t_cmd *cur_cmd);
void			redir_out_append(t_token **cur_token, t_cmd *cur_cmd);
int				handle_redir(t_cmd **cmd, t_token **cur_token,
					t_cmd *cur_cmd, t_shell shell);
int				while_add_cmd(t_shell shell, t_token *cur_token,
					t_cmd *cur_cmd, t_cmd **cmd);
int				add_cmd_node(t_shell shell, t_cmd **cmd, t_token *tokens);
int				nb_of_quotes(char *token);
char			*no_quotes(char *token);
t_token_type	which_type(char *token);
void			display_node(t_token *list);
void			display_cmd(t_cmd *cmd);
int				valid_nb_quote(char *str);
void			free_cmd(t_cmd *cmd);
void			free_tokens(t_token *tokens);
int				valid_syntax(t_token *tokens);
char			**first_equal(char *str);
void			free_chars(char **tab);
t_env			*new_env_node(char *envp_entry);
void			set_env(t_env **var, char **envp);
char			*get_env_value(t_env *env, char *name);
void			display_env(t_env *var);
char			*handle_dollar(char *str, int *i, t_shell shell, int flag);
char			*expansion(char *str, t_shell shell);
void			add_node(t_token **tokens, char *token, t_shell shell);
void			handle_left_redir(char *str, t_token **tokens,
					int *i, t_shell shell);
void			handle_right_redir(char *str, t_token **tokens,
					int *i, t_shell shell);
void			handle_operator(char *str, t_token **tokens,
					int *i, t_shell shell);
void			tok_space(char *str, t_token **tokens,
					t_parse *p, t_shell shell);
void			tok_operator(char *str, t_token **tokens,
					t_parse *p, t_shell shell);
void			tokenise_loop(char *str, t_token **tokens,
					t_parse *p, t_shell shell);
void			tokenisation(char *str, t_token **tokens, t_shell shell);
void			free_env(t_shell *shell);
void			main_loop(char **envp);
void			command_control(t_cmd *com_to_exec,
					t_shell *shell, t_token *tokens);
char			*get_env_value(t_env *env, char *name);
void			set_env(t_env **var, char **envp);
t_env			*new_env_node(char *envp_entry);
void			free_chars(char **tab);
char			**first_equal(char *str);
void			ft_cd(char *str, t_env *first_env);
void			ft_which_cd(char *str, t_env *pwd, t_env *home);
void			ft_cd_curdir(t_env *pwd);
void			ft_echo_with_redirect(char **args, char *redirection);
void			ft_echo_n_with_redirect(char **args, char *redirection);
void			ft_echo_n(char **args, char *redirection);
void			ft_echo(char **args, char *redirection);
void			ft_exec(char *str, char **args, t_env *first_env);
void			ft_which_exec(char *str, char **args,
					char **envp, char *pwd);
void			ft_exec_true_path(char *str, char **args, char **envp);
void			ft_exec_relative_path(char *str, char **args,
					char **envp, char *pwd);
char			*ft_enlever_str(char *str);
char			*ft_rajouter_str(char *str);
int				ft_is_execute(char *str);
char			**ft_envp(t_env *first_env);
t_env			*ft_find_pwd(t_env *env);
void			ft_exit(int exit_status, t_token *tokens,
					t_cmd *cmd, t_shell shell);
void			ft_export(t_env **env, char *name);
void			ft_free_env(t_env *var);
void			ft_pwd(t_env *pwd);
void			ft_unset(t_env **first_env, char *var_to_unset);
void			ft_unset_two(t_env **first_env, char *var_to_unset);
void			memory_alloc_error(void);
void			ft_env(t_env *first_env);
void			ft_cd(char *str, t_env *first_env);
void			ft_which_cd(char *str, t_env *pwd, t_env *home);
void			ft_cd_curdir(t_env *pwd);
void			ft_cd_backtrack(char *str, t_env *pwd, t_env *home);
void			ft_cd_true_path(char *str, t_env *pwd);
void			ft_cd_relative_path(char *str, t_env *pwd);
void			ft_cd_with_nothing(t_env *home, t_env *pwd);

#endif
