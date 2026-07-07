/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/06/12 12:34:06 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_in_token(t_token **cur_token, t_cmd *cur_cmd)
{
	(*cur_token) = (*cur_token)->next;
	cur_cmd->input = ft_strdup((*cur_token)->token);
}

int	heredoc_token(t_cmd **cmd, t_token **cur_token,
		t_cmd *cur_cmd, t_shell shell)
{
	setup_heredoc_signal();
	(*cur_token) = (*cur_token)->next;
	cur_cmd->heredoc = read_heredoc((*cur_token)->token, shell);
	setup_signals();
	if (!cur_cmd->heredoc)
	{
		free_cmd(*cmd);
		*cmd = NULL;
		return (0);
	}
	return (1);
}

void	redir_out_token(t_token **cur_token, t_cmd *cur_cmd)
{
	(*cur_token) = (*cur_token)->next;
	cur_cmd->output = ft_strdup((*cur_token)->token);
}

void	redir_out_append(t_token **cur_token, t_cmd *cur_cmd)
{
	(*cur_token) = (*cur_token)->next;
	cur_cmd->output_append = ft_strdup((*cur_token)->token);
}

int	handle_redir(t_cmd **cmd, t_token **cur_token,
	t_cmd *cur_cmd, t_shell shell)
{
	if ((*cur_token)->token_type == REDIR_IN)
		redir_in_token(cur_token, cur_cmd);
	else if ((*cur_token)->token_type == HEREDOC)
		return (heredoc_token(cmd, cur_token, cur_cmd, shell));
	else if ((*cur_token)->token_type == REDIR_OUT)
		redir_out_token(cur_token, cur_cmd);
	else if ((*cur_token)->token_type == REDIR_OUT_APPEND)
		redir_out_append(cur_token, cur_cmd);
	return (1);
}
