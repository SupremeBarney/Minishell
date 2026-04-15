/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_control_center.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:02:12 by nipichon          #+#    #+#             */
/*   Updated: 2026/04/13 15:42:57 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_control(t_current_command *com_to_exec, t_all_files *files_dir,
							t_all_env_var *env_vars)
{
	if (com_to_exec->command == "cd")
	{
		ft_cd(com_to_exec->args[0], files_dir->current_file, files_dir);
		return ;
	}
	if (com_to_exec->command == "echo")
	{
		if (com_to_exec->option == 'n')
			ft_echo_n(com_to_exec->args[0]);
		else
			ft_echo(com_to_exec->args[0]);
		return ;
	}
	if (com_to_exec->command == "env")
		return (ft_env(com_to_exec->args[0], com_to_exec->args[1], files_dir));
	if (com_to_exec->command == "exit")
		return (ft_exit());
	if (com_to_exec->command == "export")
		return (ft_export()); ///a faire la fonction export et mettre les arg ici
	if (com_to_exec->command == "pwd")
		return (ft_pwd(files_dir->current_file));
	if (com_to_exec->command == "unset")
		return (ft_unset(com_to_exec->args[0], env_vars));
}
