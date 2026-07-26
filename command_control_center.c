/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_control_center.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:02:12 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/25 19:14:07 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_control(t_cmd *com_to_exec,
							t_shell *shell, t_token *tokens)
{
	if (ft_strncmp(com_to_exec->args[0], "cd", 3) == 0)
	{
		ft_cd(com_to_exec->args[1], shell->env);
		return ;
	}
	if (ft_strncmp(com_to_exec->args[0], "echo", 5) == 0)
	{
		/*if (ft_strncmp(com_to_exec->args[1], "-n", 3) == 0)
			ft_echo_n(com_to_exec->args, com_to_exec->output);
		else*/
		ft_echo(com_to_exec->args, com_to_exec->output);
		return ;
	}
	if (ft_strncmp(com_to_exec->args[0], "env", 4) == 0)
		return (ft_env(shell->env));
	if (ft_strncmp(com_to_exec->args[0], "exit", 5) == 0)
		return (ft_exit(shell->exit_status, tokens, com_to_exec, *shell));
	if (ft_strncmp(com_to_exec->args[0], "export", 7) == 0)
		return (ft_export(&shell->env, com_to_exec->args[1]));
	if (ft_strncmp(com_to_exec->args[0], "pwd", 4) == 0)
		return (ft_pwd(shell->env));
	if (ft_strncmp(com_to_exec->args[0], "unset", 6) == 0)
		return (ft_unset(&shell->env, com_to_exec->args[1]));
	if (ft_is_execute(com_to_exec->args[0]) == 1)
		return (ft_exec(com_to_exec->args[0], com_to_exec->args, shell->env));
	else
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(com_to_exec->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

int	ft_is_execute(char *str)
{
	if ((str[0] == '.' && str[1] == '/') || (str[0] == '/')) // Pourquoi str[0]== '/' ?
		return (1);
	return (0);
}
