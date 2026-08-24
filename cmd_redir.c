/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/08/24 17:29:38 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_in_token(t_token **cur_token, t_cmd *cur_cmd, t_shell *shell)
{
	(*cur_token) = (*cur_token)->next;
	free(cur_cmd->input);
	cur_cmd->input = ft_strdup((*cur_token)->token);
	cur_cmd->input_rank = shell->rank;
}

int	heredoc_token(t_cmd **cmd, t_token **cur_token,
		t_cmd *cur_cmd, t_shell *shell)
{
	(*cur_token) = (*cur_token)->next;
	free(cur_cmd->heredoc);
	cur_cmd->heredoc = read_heredoc((*cur_token)->token, shell,
			!(*cur_token)->had_quotes);
	if (!cur_cmd->heredoc)
	{
		free_cmd(*cmd);
		*cmd = NULL;
		return (0);
	}
	cur_cmd->input_rank = shell->rank;
	return (1);
}

void	redir_out_token(t_token **cur_token, t_cmd *cur_cmd, t_shell *shell)
{
	(*cur_token) = (*cur_token)->next;
	free(cur_cmd->output);
	cur_cmd->output = ft_strdup((*cur_token)->token);
	cur_cmd->output_rank = shell->rank;
}

void	redir_out_append(t_token **cur_token, t_cmd *cur_cmd, t_shell *shell)
{
	(*cur_token) = (*cur_token)->next;
	free(cur_cmd->output_append);
	cur_cmd->output_append = ft_strdup((*cur_token)->token);
	cur_cmd->output_rank = shell->rank;
}

int	handle_redir(t_cmd **cmd, t_token **cur_token,
	t_cmd *cur_cmd, t_shell *shell)
{
	shell->rank++;
	if ((*cur_token)->token_type == REDIR_IN)
		redir_in_token(cur_token, cur_cmd, shell);
	else if ((*cur_token)->token_type == HEREDOC)
		return (heredoc_token(cmd, cur_token, cur_cmd, shell));
	else if ((*cur_token)->token_type == REDIR_OUT)
		redir_out_token(cur_token, cur_cmd, shell);
	else if ((*cur_token)->token_type == REDIR_OUT_APPEND)
		redir_out_append(cur_token, cur_cmd, shell);
	return (1);
}
