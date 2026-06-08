/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:31:14 by nipichon          #+#    #+#             */
/*   Updated: 2026/06/05 16:35:37 by alexfran         ###   ########.fr       */
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
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
}	t_shell;

char			*strjoin_free(char *s1, char *s2);
char			*read_heredoc(char *delimiter, t_shell shell);
int				nb_of_tokens(t_token *token);
void			init_cmd(t_cmd *cmd);
int				add_cmd_node(t_cmd **cmd, t_token *tokens, t_shell shell);
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
void			set_env(t_env **var, char **envp);
void			display_env(t_env *var);
char			*get_env_value(t_env *env, char *name);
char			*handle_dollar(char *str, int *i, t_shell shell);
char			*expansion(char *str, t_shell shell);
void			add_node(t_token **tokens, char *token, t_shell shell);
void			handle_operator(char *str, t_token **tokens, int *i,
int *start_token, t_shell shell);
void			tokenisation(char *str, t_token **tokens, t_shell shell);
void			free_env(t_shell *shell);
void			main_loop(char **envp);

#endif
