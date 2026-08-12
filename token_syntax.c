/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 16:17:15 by alexfran          #+#    #+#             */
/*   Updated: 2026/07/25 19:49:31 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_double_redir(t_token *tmp)
{
	if (tmp->token_type == REDIR_IN
		&& tmp->next->token_type == REDIR_IN)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `<'\n", 2);
		return (1);
	}
	if (tmp->token_type == REDIR_OUT
		&& tmp->next->token_type == REDIR_OUT)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `>'\n", 2);
		return (1);
	}
	if (tmp->token_type == REDIR_OUT_APPEND
		&& tmp->next->token_type == REDIR_OUT_APPEND)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 2);
		return (1);
	}
	if (tmp->token_type == HEREDOC
		&& tmp->next->token_type == HEREDOC)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `<<'\n", 2);
		return (1);
	}
	return (0);
}

static int	unexpected_token(t_token_type type)
{
	if (type == REDIR_IN)
		ft_putstr_fd("bash: syntax error near unexpected token `<'\n", 2);
	else if (type == REDIR_OUT)
		ft_putstr_fd("bash: syntax error near unexpected token `>'\n", 2);
	else if (type == REDIR_OUT_APPEND)
		ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 2);
	else if (type == HEREDOC)
		ft_putstr_fd("bash: syntax error near unexpected token `<<'\n", 2);
	else if (type == PIPE)
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
	return (1);
}

static int	check_token_syntax(t_token *tmp)
{
	if ((tmp->token_type >= REDIR_IN
			&& tmp->token_type <= REDIR_OUT_APPEND && !tmp->next)
		|| (tmp->token_type == REDIR_IN && tmp->next->token_type == REDIR_OUT))
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	if (tmp->token_type >= REDIR_IN && tmp->token_type <= REDIR_OUT_APPEND
		&& tmp->token_type != REDIR_OUT && tmp->next->token_type == PIPE)
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
	if (check_double_redir(tmp))
		return (1);
	if (tmp->token_type == PIPE && tmp->next
		&& tmp->next->token_type == PIPE)
		return (unexpected_token(PIPE));
	if ((tmp->token_type != WORD && tmp->token_type != PIPE)
		&& tmp->next && tmp->next->token_type != WORD)
		return (unexpected_token(tmp->next->token_type));
	return (0);
}

int	valid_syntax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (!tmp)
		return (0);
	if (tmp->token_type == PIPE)
	{
		if (tmp->next && tmp->next->token_type == PIPE)
		{
			ft_putstr_fd("bash: syntax error near unexpected token `||'\n", 2);
			return (1);
		}
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	while (tmp)
	{
		if (check_token_syntax(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
