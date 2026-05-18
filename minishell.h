/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:31:14 by nipichon          #+#    #+#             */
/*   Updated: 2026/05/05 14:42:37 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "libftprintf/ft_printf.h"

typedef struct s_cmd {
	char	*cmd;
	char	*argument;
	char	*destination;
}	t_cmd;


typedef enum	e_token_type {
	WORD,
	PIPE,
	REDIR_IN,
	HEREDOC,
	REDIR_OUT,
	REDIR_OUT_APPEND,
}	t_token_type;

typedef struct	s_environment_variable {
	void	*variable;
	int		index;
}	t_environment_variable;

typedef struct s_token {
	char			*token;
	t_token_type	token_type;
	struct s_token	*next;
}	t_token;


#endif
