/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/08/22 15:48:12 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->heredoc = NULL;
	cmd->output_append = NULL;
	cmd->input_rank = 0;
	cmd->output_rank = 0;
	cmd->next = NULL;
}

int	pipe_token(t_cmd **cur_cmd, t_token **cur_token, int *i)
{
	(*cur_cmd)->args[*i] = NULL;
	*i = 0;
	(*cur_token) = (*cur_token)->next;
	(*cur_cmd)->next = ft_calloc(1, sizeof(t_cmd));
	if (!(*cur_cmd)->next)
		return (0);
	(*cur_cmd) = (*cur_cmd)->next;
	(*cur_cmd)->args = ft_calloc(nb_of_tokens(*cur_token) + 1,
			sizeof(char *));
	if (!(*cur_cmd)->args)
		return (0);
	return (1);
}

int	while_add_cmd(t_shell *shell, t_token *cur_token,
	t_cmd *cur_cmd, t_cmd **cmd)
{
	int		i;

	i = 0;
	shell->rank = 0;
	while (cur_token)
	{
		if (cur_token->token_type == WORD && (cur_token->had_quotes
				|| cur_token->token[0]))
			cur_cmd->args[i++] = ft_strdup(cur_token->token);
		else if (cur_token->token_type == PIPE)
		{
			if (!pipe_token(&cur_cmd, &cur_token, &i))
				return (0);
			shell->rank = 0;
			continue ;
		}
		else if (!handle_redir(cmd, &cur_token, cur_cmd, shell))
			return (0);
		cur_token = cur_token->next;
	}
	cur_cmd->args[i] = NULL;
	return (1);
}

int	add_cmd_node(t_shell *shell, t_cmd **cmd, t_token *tokens)
{
	t_token	*cur_token;
	t_cmd	*cur_cmd;

	cur_token = tokens;
	*cmd = ft_calloc(1, sizeof(t_cmd));
	if (!(*cmd))
		return (0);
	init_cmd(*cmd);
	cur_cmd = *cmd;
	cur_cmd->args = ft_calloc(nb_of_tokens(cur_token) + 1, sizeof(char *));
	if (!cur_cmd->args)
		return (0);
	if (!while_add_cmd(shell, cur_token, cur_cmd, cmd))
		return (1);
	return (0);
}
