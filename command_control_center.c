/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_control_center.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:02:12 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/12 14:46:10 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_redirections(t_cmd *cmd)
{
	if (cmd->output_rank && cmd->output_rank < cmd->input_rank)
	{
		if (apply_output(cmd) == -1)
			return (-1);
		return (apply_input(cmd));
	}
	if (apply_input(cmd) == -1)
		return (-1);
	return (apply_output(cmd));
}

void	dispatch_command(t_cmd *com_to_exec,
							t_shell *shell, t_token *tokens)
{
	if (!com_to_exec->args[0])
		return ;
	else if (ft_strncmp(com_to_exec->args[0], "cd", 3) == 0)
	{
		ft_cd(com_to_exec->args[1], shell->env, com_to_exec->args,
			&shell->exit_status);
		return ;
	}
	else if (ft_strncmp(com_to_exec->args[0], "echo", 5) == 0)
	{
		ft_echo(com_to_exec->args);
		return ;
	}
	else if (ft_strncmp(com_to_exec->args[0], "env", 4) == 0)
		return (ft_env(shell->env));
	else if (ft_strncmp(com_to_exec->args[0], "exit", 5) == 0)
		return (ft_exit(shell->exit_status, tokens, com_to_exec, *shell));
	else if (ft_strncmp(com_to_exec->args[0], "export", 7) == 0)
		return (ft_export(&shell->env, com_to_exec->args,
				&shell->exit_status));
	else
		dispatch_command_second(com_to_exec, shell);
}

void	command_control(t_cmd *com_to_exec,
							t_shell *shell, t_token *tokens)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (apply_redirections(com_to_exec) == -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return ;
	}
	dispatch_command(com_to_exec, shell, tokens);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
