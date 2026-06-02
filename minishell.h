/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:31:14 by nipichon          #+#    #+#             */
/*   Updated: 2026/06/02 15:13:25 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "libftprintf/ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

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

#endif
