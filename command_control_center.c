/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_control_center.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:02:12 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/17 15:35:01 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_control(t_cmd *com_to_exec,
							t_shell *shell)
{
	if (ft_strncmp(com_to_exec->args[0], "cd", 3) == 0)
	{
		ft_cd(com_to_exec->args[1], shell->env);
		return ;
	}
	if (ft_strncmp(com_to_exec->args[0], "echo", 5) == 0)
	{
		if (ft_strncmp(com_to_exec->args[1], "-n", 3) == 0)
			ft_echo_n(com_to_exec->args, com_to_exec->output);
		else
			ft_echo(com_to_exec->args, com_to_exec->output);
		return ;
	}
	if (ft_strncmp(com_to_exec->args[0], "env", 4) == 0)
		return (ft_env(shell->env));
	if (ft_strncmp(com_to_exec->args[0], "exit", 5) == 0)
		return (ft_exit(shell->exit_status));
	if (ft_strncmp(com_to_exec->args[0], "export", 7) == 0)
		return (ft_export(&shell->env, com_to_exec->args[1]));
	if (ft_strncmp(com_to_exec->args[0], "pwd", 4) == 0)
		return (ft_pwd(shell->env));
	if (ft_strncmp(com_to_exec->args[0], "unset", 6) == 0)
		return (ft_unset(&shell->env, com_to_exec->args[1]));
}
