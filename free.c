/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/06/15 11:42:01 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd)
	{
		i = 0;
		tmp = cmd->next;
		if (cmd->args)
		{
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		free(cmd->input);
		free(cmd->heredoc);
		free(cmd->output);
		free(cmd->output_append);
		free(cmd);
		cmd = tmp;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return ;
	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->token);
		free(tokens);
		tokens = tmp;
	}
}

void	free_env(t_shell *shell)
{
	t_env	*tmp;

	if (!shell->env)
		return ;
	while (shell->env)
	{
		tmp = shell->env->next;
		free(shell->env->name);
		free(shell->env->value);
		free(shell->env);
		shell->env = tmp;
	}
	shell->env = NULL;
}
