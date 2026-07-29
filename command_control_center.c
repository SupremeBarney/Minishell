/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_control_center.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:02:12 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/29 16:51:26 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_control(t_cmd *com_to_exec,
							t_shell *shell, t_token *tokens)
{
	if (!com_to_exec->args[0])
		return ;
	else if (ft_strncmp(com_to_exec->args[0], "cd", 3) == 0)
	{
		ft_cd(com_to_exec->args[1], shell->env);
		return ;
	}
	else if (ft_strncmp(com_to_exec->args[0], "echo", 5) == 0)
	{
		/*if (ft_strncmp(com_to_exec->args[1], "-n", 3) == 0)
			ft_echo_n(com_to_exec->args, com_to_exec->output);
		else*/
		ft_echo(com_to_exec->args, com_to_exec->output);
		return ;
	}
	else if (ft_strncmp(com_to_exec->args[0], "env", 4) == 0)
		return (ft_env(shell->env));
	else if (ft_strncmp(com_to_exec->args[0], "exit", 5) == 0)
		return (ft_exit(shell->exit_status, tokens, com_to_exec, *shell));
	else if (ft_strncmp(com_to_exec->args[0], "export", 7) == 0)
		return (ft_export(&shell->env, com_to_exec->args));
	else if (ft_strncmp(com_to_exec->args[0], "pwd", 4) == 0)
		return (ft_pwd(shell->env));
	else if (ft_strncmp(com_to_exec->args[0], "unset", 6) == 0)
		return (ft_unset(&shell->env, com_to_exec->args[1]));
	else if (ft_is_execute(com_to_exec->args[0], shell->env, com_to_exec->args, 0) == 1)
		return (ft_exec(com_to_exec->args[0], com_to_exec->args, shell->env));
	else if (ft_is_execute(com_to_exec->args[0], shell->env, com_to_exec->args, 0) == 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(com_to_exec->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

int	ft_is_execute(char *str, t_env *first_env, char **args, int i)
{
	t_env	*parseur;
	char	**path;
	char	**envp;
	char	*tmp;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		parseur = first_env;
		i = 0;
		while (parseur)
		{
			if (ft_strncmp(parseur->name, "PATH", 5) == 0)
			{
				envp = ft_envp(first_env);
				path = ft_split (parseur->value, ':');
				while (path[i])
				{
					tmp = ft_strjoin(path[i], "/");
					path[i] = ft_strjoin(tmp, str);
					if (execve(path[i], args, envp) != -1)
						return (2);
					i++;
				}
			}
			parseur = parseur->next;
		}
	}
	if (pid > 0)
		waitpid(pid, NULL, 0);
	if (pid < 0)
		perror("error");	
	if ((str[0] == '.' && str[1] == '/') || (str[0] == '/')) 
		return (1);
	return (0);
}
